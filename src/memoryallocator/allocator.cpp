#include "allocator.h"

struct Linear_block {
    size_t size : 31;
    bool free : 1;
    Linear_block * prev;
    Linear_block * next;
};

/*
    |       |       |       |       |       |
    node0    
    |block1|             mem              |block2|
    
*/

LinearAllocator::LinearAllocator(void * base, size_t size) {
    // base is the start address of the allocation region
    head = reinterpret_cast<Linear_block*>(base);
    tail = reinterpret_cast<char*>(head) + size;
}

void * LinearAllocator::allocate(size_t size) {
    Linear_block * current = head;
    while (current != tail){
        if (current->free && reinterpret_cast<char*>(current->next) - reinterpret_cast<char*>(current) >= size + sizeof(Linear_block)){
            if (reinterpret_cast<char*>(current->next) - reinterpret_cast<char*>(current) >= size + sizeof(Linear_block) * 2){
                Linear_block * new_block = reinterpret_cast<Linear_block*>(reinterpret_cast<char*>(current) + sizeof(Linear_block) + size);
                new_block->free = true;
                new_block->prev = current;
                new_block->next = current->next;
                if (current->next) current->next->prev = new_block;
                current->next = new_block;
            }
            current->free = false;
            return reinterpret_cast<void*>(reinterpret_cast<char*>(current) + sizeof(Linear_block));
        }
        current = current->next;
    }
    return nullptr;
}

int LinearAllocator::deallocate(void * ptr) {
    Linear_block * block = reinterpret_cast<Linear_block*>(reinterpret_cast<char*>(ptr) - sizeof(Linear_block));
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