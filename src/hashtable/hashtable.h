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

template <class K, class V, class C, V EmptyVal, CollisionHandler handler, HashFunc<K> hash, CompressFunc<K, C> compress>
class HashTable {
    typedef int (* HashFunc)(K key);
    struct Pair {
        K key;
        V val;
    };
protected:
    size_t size_;
    Pair * table_;
    Allocator * allocator_;
    HashFunc * hash_func_;
public:
    HashTable(Allocator * allocator, HashFunc * func) : allocator_(allocator), hash_func_(func) {}
    void put(K key, V val) {
               
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
