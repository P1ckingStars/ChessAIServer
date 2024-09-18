#ifndef BSS_H
#define BSS_H

#include "../util/thread_safe_pointer.hpp"
#include "../../dependency/include/simple_mutex.hpp"
#include "../hashtable/hashable.hpp"
#include <cstdint>

#define RPC_SUBMIT_TASK "submit_task"

struct Task {
    CompressedBoard board;
    uint8_t task_id;
};
struct Reponse {
    int16_t move;
    uint8_t task_id;
};

template <class T>
struct RoundBuffer: LockableProxy<SimpleMutex> {
    std::size_t head = 0;
    std::size_t tail = 0;
    T buffer[10];
    
    bool push(T val) {
        size_t next_tail = (tail + 1) % 10;
        if (next_tail != head) { // there's space
            buffer[tail].move = val.move;
            tail = next_tail;
            return true;
        }
        return false;
    }

    bool pop(T & res) {
        if (head != tail) {
            T task = buffer[head];
            head = (head + 1) % 10;
            res = task;
            return true;
        }
        return false;
    }
};

struct BSS {
    RoundBuffer<Task>taskQueue;
    ThreadSafePtr<RoundBuffer<Task>> taskQueuePtr {&taskQueue};
};

/*

|   bss   |                             LinearAllocator                             |

*/

#endif
