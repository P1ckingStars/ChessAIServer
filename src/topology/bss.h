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
struct Response {
    int16_t move;
    bool valid;
};

template <class T, int size>
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

#define MAX_REQUEST 256
#define MAX_WAITING_QUEUE 32
struct BSS {
    ThreadSafePtr<RoundBuffer<Task, MAX_WAITING_QUEUE>> task_queue_ptr {&task_queue};
    ThreadSafePtr<RoundBuffer<uint8_t, MAX_REQUEST>> request_slot_ptr {&request_slot};
    Response responses[MAX_REQUEST];
private:
    RoundBuffer<Task, MAX_WAITING_QUEUE> task_queue;
    RoundBuffer<uint8_t, MAX_REQUEST> request_slot;
};

/*

|   bss   |                             LinearAllocator                             |

*/

#endif
