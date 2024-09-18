#include <cstdint>
#include <rpc/server.h>
#include "bss.h"
#include <stddef.h>
#include <vector>



int dsm_main(char * mem_region, size_t length, int argc, char * argv[]) {
    BSS *bss = (BSS *)mem_region;
    char *base = mem_region + 4096;
    for (int i = 0; i < MAX_REQUEST; i++) {
        bss->responses[i].valid = false;
        bss->request_slot_ptr->deref()->push(i);
    }

    rpc::server balancer(8080);
    balancer.bind(RPC_SUBMIT_TASK, [bss](Task task) {
        uint8_t task_id;
        while(!bss->request_slot_ptr->deref()->pop(task_id));
        while(!bss->task_queue_ptr->deref()->push(task));
        while (!bss->responses[task_id].valid);
    });

    balancer.async_run(16);

    std::cout << "Balancer is running..." << std::endl;
    return 0;
}
