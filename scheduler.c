#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "constants.h"

int compare_fcfs(const void *a, const void *b){
    // arrival time으로 정렬
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    // 음수면 순서 p1,p2
    // 양수면 순서 p2,p1
    return p1->arrival_time - p2->arrival_time;

}

void fcfs(Process *processes, int num_process) {
    
    // 복사해서 정렬
    Process processes_copy[MAX_PROCESS];
    memcpy(processes_copy, processes, sizeof(Process)*num_process);

    qsort(processes_copy, num_process, sizeof(Process), compare_fcfs);

    Queue ready_queue;
    init_queue(&ready_queue);
    for (int i=0; i < 5; i++) {
        enqueue(&ready_queue, &processes_copy[i]);
    }

    int current_time=0;

    while (!is_empty(&ready_queue)) {
        Process *p = dequeue(&ready_queue);

        if (current_time<p->arrival_time){
            current_time=p->arrival_time;
        }

        p->start_time=current_time;
        p->waiting_time=current_time-p->arrival_time;
        current_time+=p->cpu_burst_time;
        p->complete_time=current_time;
        p->turnaround_time=p->complete_time-p->arrival_time;

    }

    // 간트 차트
    for (int i=0; i<num_process; i++) {
        printf("PID %d (%d~%d) | ", processes_copy[i].pid, processes_copy[i].start_time, processes_copy[i].complete_time);
    }


}
