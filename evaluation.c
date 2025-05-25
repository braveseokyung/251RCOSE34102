#include <stdio.h>
#include "process.h"

void evaluate(Process *processes, int num_process, const char *algorithm_name) {
    
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    for (int i = 0; i < num_process; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        // printf("process waiting time : %d\n",processes[i].waiting_time);
        // printf("process turnaround time : %d\n",processes[i].turnaround_time);

    }

    float avg_waiting_time = total_waiting_time / num_process;
    float avg_turnaround_time = total_turnaround_time / num_process;

    printf("%s Evaluation:\n", algorithm_name);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("\n");
}
