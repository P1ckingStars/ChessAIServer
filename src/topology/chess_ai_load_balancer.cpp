#include "bss.h"
#include <cstdint>
#include <rpc/server.h>
#include <stddef.h>
#include <vector>
#include <new>

int dsm_main(char *mem_region, size_t length, int argc, char *argv[]) {
  DEBUG_LOG("----------Start Server----------");
  BSS *bss = (BSS *)mem_region ;
  new (bss) BSS();
  char *base = mem_region + 4096;
  DEBUG_LOGF("bss addr: %lx\n", (intptr_t)bss);
  for (int i = 0; i < MAX_REQUEST; i++) {
    bss->responses[i].valid = false;
    bss->request_slot_ptr->push(i);
  }
  printf("finished queue initialization");

  rpc::server balancer(8080);
  balancer.bind(RPC_SUBMIT_TASK, [bss](CompressedBoard board) {
    Task task;
    task.board = board;
    uint8_t task_id;
    while (!bss->request_slot_ptr->pop(task_id))
      ;
    while (!bss->task_queue_ptr->push(task))
      ;
    while (!bss->responses[task_id].valid)
      ;
  });

  balancer.async_run(16);

  std::cout << "Balancer is running..." << std::endl;
  return 0;
}
