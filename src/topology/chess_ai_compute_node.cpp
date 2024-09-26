#include "bss.h"
#include <cstdio>
#include <stddef.h>
/*
compute: dequeue task, work on task -> return back to balancer node
balancer: req from client -> task queue -> get finished task and return to
client

client: -> balancer
*/

void process_task(BSS *bss, Task task) {
  // TODO
}

int dsm_main(char *mem_region, size_t length, int argc, char *argv[]) {
  printf("----------Start Compute Node----------");
  printf("%lu\n", sizeof(BSS));
  BSS *bss = (BSS *)mem_region;
  char *base = mem_region + 4096;

  Task task;
  while (1) {
    while (!bss->task_queue_ptr->pop(task))
      ;
    process_task(bss, task);
  }

  return 0;
}
