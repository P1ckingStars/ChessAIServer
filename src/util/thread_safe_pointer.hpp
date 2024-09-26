
template <class M>
class LockableProxy {
    M mutex;
public:
    void lock() {
        mutex.lock();
    }
    void unlock() {
        mutex.unlock();
    }
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
    T * deref() const {
        return ptr_;
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
    }
    ~ThreadSafePtr() {
    } 
    TmpLock<T> operator->() const {
        return TmpLock(ptr_);
    }
};

