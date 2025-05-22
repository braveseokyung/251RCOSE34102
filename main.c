#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "config.h"

int main() {

    Process processes[5];
    Queue ready_queue;

    create_process(processes, 5, 42);
    init_queue(&ready_queue);

    for (int i=0; i < 5; i++) {
        enqueue(&ready_queue, &processes[i]);
    }

    print_queue(&ready_queue, "Ready");

    Process *p = dequeue(&ready_queue);

    print_queue(&ready_queue, "Ready");

    return 0;
}