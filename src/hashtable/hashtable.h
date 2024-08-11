#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <unordered_map>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "../chess/chess.hpp"
#include "../memoryallocator/allocator.h"

using namespace std;

typedef size_t(* CollisionHandler)(size_t index, size_t collision_count, size_t size);

template <class K>
class HashFunc {
    virtual int operator()(K key) = 0;
};

template <class K, class C>
class CompressFunc {
    virtual C operator()(K key) = 0;
};

template <class T>
class TmpLock {
private:
    T * ptr_;
public:
    TmpLock(T * ptr) : ptr_(ptr) {
        ptr_->lock();
    } 
    ~TmpLock() {
        ptr_->unlock();
    } 
    T * operator->() const {
        return ptr_;
    }
};

template <class T>
class ThreadSafePtr {
private:
    T * ptr_;
public:
    ThreadSafePtr(T * ptr) : ptr_(ptr) {
        ptr_->lock();
    }
    ~ThreadSafePtr() {
        ptr_->unlock();
    } 
    TmpLock<T> * operator->() const {
        return TmpLock(ptr_);
    }
};

template <class K, class V, class C, V EmptyVal, CollisionHandler handler, 
    HashFunc<K> hash, CompressFunc<K, C> compress>
class HashTable {
    typedef int (* HashFunc)(K key);
    struct Pair {
        C key;
        V val;
    };
protected:
    size_t size_;
    size_t reserved_size_;
    Pair * table_;
    Allocator * allocator_;
    HashFunc * hash_func_;
    bool can_grow_;
public:
    HashTable(Allocator * allocator, HashFunc * func, 
        size_t reserved_size, bool can_grow) : 
            allocator_(allocator), 
            hash_func_(func), 
            can_grow_(can_grow), 
            reserved_size_(reserved_size), 
            size_(0) {
        table_ = allocator_->allocate(sizeof(Pair) * reserved_size);   
    }
    bool extend() {

    }
    bool shrink() {

    }
    bool put(K key, V val) {
        if (size_ * 2 > reserved_size_) {
            if (can_grow_ ? !extend() : 1) return false;
        }
        size_t code = hash(key);
        C compressed_key = compress(key);
        size_t index;
        int count = 0;
        for (index = code % size_; table_[index].has_value && table_[index].Key != compressed_key;
            index = handler(index, count++, reserved_size_));
        if (table_[index].val != EmptyVal) return false;
        table_[index].val = val;
        table_[index].key = compressed_key;
        return true;
    }
    V get(K key) {

    }
    V& operator[](K key) {

    }
    bool contains(K key) {
        get(key) == EmptyVal;
    }
    // allocator_->allocate(size);
};



#endif
