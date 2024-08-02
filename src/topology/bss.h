#ifndef BSS_H
#define BSS_H

struct Task {
    int16_t move;

}

struct RoundBuffer {
};

struct BSS {
    Task tasks[10];
};

/*

|   bss   |                             LinearAllocator                             |

*/

#endif