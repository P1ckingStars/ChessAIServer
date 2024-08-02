#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <stddef.h>

class Allocator {
public:
    virtual void * allocate(size_t size)        = 0;
    virtual int deallocate(void * ptr)      = 0;
};

struct LinearBlock;

class LinearAllocator: Allocator {
private:
    LinearBlock * head;
    LinearBlock * tail;
    size_t taken_size;
public:
    LinearAllocator(void * base, size_t size);
    void * allocate(size_t size) override;
    int deallocate(void * ptr) override;
};

typedef LinearAllocator DSMAllocator;

#endif
