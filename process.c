#include <stdio.h>
#include <stdlib.h>
#include "process.h"

void create_process(Process *processes, int num_process, int seed) {
    srand(seed);

    for (int i=0; i < num_process; i++) {
        processes[i].pid = i;
        processes[i].arrival_time = rand() % 6;
        processes[i].cpu_burst_time = rand() % 20 + 1;
        processes[i].priority = rand () % num_process + 1;
    }

    printf("%d processes created.\n",num_process);
    printf("pid\t|CPU burst time\t|Arrival time\t|Priority\t\n");
    for (int i=0; i < num_process; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\n", processes[i].pid, processes[i].cpu_burst_time, processes[i].arrival_time, processes[i].priority);
    } 

}
