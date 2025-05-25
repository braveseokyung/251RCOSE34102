#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "config.h"
#include "constants.h"
#include "scheduler.h"

int main() {

    Process processes[MAX_PROCESS];
    Queue ready_queue;

    create_process(processes, NUM_PROCESS, 42);

    // fcfs(processes,NUM_PROCESS);
    // nonpre_sjf(processes,NUM_PROCESS);
    // nonpre_priority(processes,NUM_PROCESS);
    // pre_sjf(processes, NUM_PROCESS);
    pre_priority(processes, NUM_PROCESS);
    // init_queue(&ready_queue);

    // for (int i=0; i < 5; i++) {
    //     enqueue(&ready_queue, &processes[i]);
    // }

    // print_queue(&ready_queue, "Ready");

    // Process *p = dequeue(&ready_queue);

    // print_queue(&ready_queue, "Ready");

    return 0;
}