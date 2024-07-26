#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <stddef.h>

class Allocator {
public:
    Allocator(void * base, size_t size);
    void * allocate(size_t size);
    int deallocate(void * ptr);
};

#endif