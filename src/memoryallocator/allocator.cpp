#include "allocator.h"

struct LinearBlock {
    size_t size : 31;
    bool free : 1;
    LinearBlock * prev;
    LinearBlock * next;
};

/*
    |       |       |       |       |       |
    node0    
    |block1|             mem              |block2|
    
*/

LinearAllocator::LinearAllocator(void * base, size_t size) {
    // base is the start address of the allocation region
    head = reinterpret_cast<LinearBlock*>(base);
    tail = reinterpret_cast<LinearBlock*>(reinterpret_cast<char*>(head) + size);
}

void * LinearAllocator::allocate(size_t size) {
    LinearBlock * current = head;
    while (current != tail){
        if (current->free && reinterpret_cast<char*>(current->next) - reinterpret_cast<char*>(current) >= size + sizeof(LinearBlock)){
            if (reinterpret_cast<char*>(current->next) - reinterpret_cast<char*>(current) >= size + sizeof(LinearBlock) * 2){
                LinearBlock * new_block = reinterpret_cast<LinearBlock*>(reinterpret_cast<char*>(current) + sizeof(LinearBlock) + size);
                new_block->free = true;
                new_block->prev = current;
                new_block->next = current->next;
                if (current->next) current->next->prev = new_block;
                current->next = new_block;
            }
            current->free = false;
            return reinterpret_cast<void*>(reinterpret_cast<char*>(current) + sizeof(LinearBlock));
        }
        current = current->next;
    }
    return nullptr;
}

int LinearAllocator::deallocate(void * ptr) {
    LinearBlock * block = reinterpret_cast<LinearBlock*>(reinterpret_cast<char*>(ptr) - sizeof(LinearBlock));
    block->free = true;
    if (block->prev && block->prev->free){
        block->prev->next = block->next;
        if (block->next){
            block->next->prev = block->prev;
        }
        block = block->prev;
    }

    if (block->next && block->next->free){
        block->next = block->next->next;
        if (block->next){
            block->next->prev = block;
        }
    }
}
