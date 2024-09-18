#include <rpc/server.h>
#include "bss.h"
#include <stddef.h>


int dsm_main(char * mem_region, size_t length, int argc, char * argv[]) {
    BSS *bss = (BSS *)mem_region;
    char *base = mem_region + 4096;

    rpc::server balancer(8080);
    balancer.bind(RPC_SUBMIT_TASK, [bss](Task task) {
        while(!bss->taskQueue.push(task)) { }
    });

    balancer.async_run(16);

    std::cout << "Balancer is running..." << std::endl;
    return 0;
}
