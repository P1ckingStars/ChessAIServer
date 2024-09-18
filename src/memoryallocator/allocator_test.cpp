#include "allocator.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

int main() {
    void * base = malloc(4096);
    DSMAllocator * allocator = new DSMAllocator(base, 4096);
    struct alloc_blk {
        int size;
        int8_t id;
    };
    std::unordered_map<intptr_t, int> mp;
    #define SIZE 10
    int alloc_size[SIZE] = {100, 20, 40, 300, 127, 256, 64, 500, 23, 67}; 
    alloc_blk blks[SIZE];
    for (int8_t i = 0; i < SIZE; i++) {
        blks[i].size = alloc_size[i];
        blks[i].id = i;
        auto addr = allocator->allocate(blks[i].size);
        mp[(intptr_t)addr] = i;
        memset(addr, i, blks[i].size);
    }
    for (auto entry : mp) {
        for (int i = 0; i < blks[entry.second].size; i++) {
            if (((int8_t *)entry.first)[i] != blks[entry.second].id) {
                printf("ERROR\n");
                return -1;
            }
        }
    }
    printf("succeed");
}
