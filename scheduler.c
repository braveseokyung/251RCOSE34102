#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "constants.h"

int compare_by_arrival(const void *a, const void *b){
    
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

    qsort(processes_copy, num_process, sizeof(Process), compare_by_arrival);

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
    printf("FCFS Gantt Chart:\n");
    for (int i=0; i<num_process; i++) {
        printf("PID %d (%d~%d) | ", processes_copy[i].pid, processes_copy[i].start_time, processes_copy[i].complete_time);
    }
    printf("\n");


}

void nonpre_sjf(Process *processes, int num_process) {

    // 복사
    Process processes_copy[MAX_PROCESS];
    memcpy(processes_copy, processes, sizeof(Process)*num_process);

    // 실행순서 저장
    Process *processes_executed[MAX_PROCESS];

    // arrival 기준으로 정렬
    qsort(processes_copy, num_process, sizeof(Process), compare_by_arrival);

    int current_time=0;
    int num_completed=0;

    while(num_completed < num_process){

        int min_burst_idx=-1;
        int min_cpu_burst_time=MAX_CPU_BURST_TIME;
        
        for (int i=0; i<num_process; i++) {
            if (processes_copy[i].arrival_time > current_time){
                break;
            }

            if(!processes_copy[i].is_completed && processes_copy[i].cpu_burst_time < min_cpu_burst_time) {

                min_cpu_burst_time = processes_copy[i].cpu_burst_time;
                min_burst_idx=i;
                
            }

        }

        if (min_burst_idx==-1) {
            current_time++;
            continue;
        }

        processes_copy[min_burst_idx].start_time=current_time;
        current_time+=processes_copy[min_burst_idx].cpu_burst_time;
        processes_copy[min_burst_idx].complete_time=current_time;
        processes_copy[min_burst_idx].turnaround_time=processes_copy[min_burst_idx].complete_time-processes_copy[min_burst_idx].arrival_time;
        processes_copy[min_burst_idx].is_completed=true;

        processes_executed[num_completed]=&processes_copy[min_burst_idx];
        num_completed++;

    }

    // 간트 차트
    printf("Non-preemptive SJF Gantt Chart:\n");
    for (int i=0; i<num_process; i++) {
        printf("PID %d (%d~%d) | ", processes_executed[i]->pid, processes_executed[i]->start_time, processes_executed[i]->complete_time);
    }
    printf("\n");

}