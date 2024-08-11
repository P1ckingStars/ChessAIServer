#include "allocator.h"

int main() {
    void * base = malloc(4096);
    DSMAllocator * allocator = new DSMAllocator(base, 4096);
}