#include "bss.h"
#include <stddef.h>
/*
compute: dequeue task, work on task -> return back to balancer node
balancer: req from client -> task queue -> get finished task and return to
client

client: -> balancer
*/

void process_task(Task task) {
  // TODO
    
}

int dsm_main(char *mem_region, size_t length, int argc, char *argv[]) {
  BSS *bss = (BSS *)mem_region;
  char *base = mem_region + 4096;

  Task task;
  while (1) {
    while (!bss->taskQueue.pop(task));
    process_task(task);
  }

  return 0;
}
