#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "constants.h"

void create_process(Process *processes, int num_process, int seed) {
    srand(seed);

    for (int i=0; i < num_process; i++) {
        processes[i].pid = i;
        processes[i].arrival_time = rand() % 6;
        processes[i].cpu_burst_time = rand() % 20 + 1;
        processes[i].remaining_time = processes[i].cpu_burst_time;
        // 10% 확률로 I/O 발생
        // if ((rand() % 100) < 10) {  
        //     processes[i].io_start_time = rand() % (processes[i].cpu_burst_time - 1) + 1;  // 최소 1틱은 CPU 돌고 나서
        //     processes[i].io_burst_time = rand() % MAX_IO_BURST_TIME;
        // } else {
        //     processes[i].io_start_time = -1;
        //     processes[i].io_burst_time = 0;
        // }
        processes[i].priority = rand () % num_process + 1;
        processes[i].is_completed = false;
    }

    printf("%d processes created.\n",num_process);
    printf("pid\t|CPU burst time\t|Arrival time\t|Priority\t\n");
    for (int i=0; i < num_process; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\n", processes[i].pid, processes[i].cpu_burst_time, processes[i].arrival_time, processes[i].priority);
    } 

}
