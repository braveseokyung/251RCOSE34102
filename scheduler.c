#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scheduler.h"
#include "constants.h"
#include "evaluation.h"

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
    Queue wait_queue;
    init_queue(&ready_queue);
    init_queue(&wait_queue);
    for (int i=0; i < num_process; i++) {
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

    evaluate(processes_copy, num_process, "FCFS");


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
        processes_copy[min_burst_idx].waiting_time=processes_copy[min_burst_idx].start_time-processes_copy[min_burst_idx].arrival_time;
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

    // 성능 분석
    evaluate(processes_copy, num_process, "Non-preemptive SJF");

}

void nonpre_priority(Process *processes, int num_process) {

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

        int min_priority_idx=-1;
        int min_priority=num_process+1;
        
        for (int i=0; i<num_process; i++) {
            if (processes_copy[i].arrival_time > current_time){
                break;
            }

            if(!processes_copy[i].is_completed && processes_copy[i].priority < min_priority) {

                min_priority = processes_copy[i].priority;
                min_priority_idx=i;
                
            }

        }

        if (min_priority_idx==-1) {
            current_time++;
            continue;
        }

        processes_copy[min_priority_idx].start_time=current_time;
        processes_copy[min_priority_idx].waiting_time=processes_copy[min_priority_idx].start_time-processes_copy[min_priority_idx].arrival_time;
        current_time+=processes_copy[min_priority_idx].cpu_burst_time;
        processes_copy[min_priority_idx].complete_time=current_time;
        processes_copy[min_priority_idx].turnaround_time=processes_copy[min_priority_idx].complete_time-processes_copy[min_priority_idx].arrival_time;
        processes_copy[min_priority_idx].is_completed=true;

        processes_executed[num_completed]=&processes_copy[min_priority_idx];
        num_completed++;

    }

    // 간트 차트
    printf("Non-preemptive Priority Gantt Chart:\n");
    for (int i=0; i<num_process; i++) {
        printf("PID %d (%d~%d) | ", processes_executed[i]->pid, processes_executed[i]->start_time, processes_executed[i]->complete_time);
    }
    printf("\n");

    // 성능 분석
    evaluate(processes_copy, num_process, "Non-preemptive Priority");

}

void pre_sjf(Process *processes, int num_process) {

        // 복사
        Process processes_copy[MAX_PROCESS];
        memcpy(processes_copy, processes, sizeof(Process)*num_process);
    
        // 시간별 실행된 프로세스 저장
        Process *executed_timeline[MAX_TIME];
    
        int current_time=0;
        int num_completed=0;
    
        while(num_completed < num_process){
    
            int min_remain_idx=-1;
            int min_remaining_time=MAX_CPU_BURST_TIME;
            // bool is_preempted=false;
            
            for (int i=0; i<num_process; i++) {

                if (processes_copy[i].arrival_time > current_time){
                    continue;
                }
    
                if(!processes_copy[i].is_completed && processes_copy[i].remaining_time < min_remaining_time) {
    
                    min_remaining_time = processes_copy[i].remaining_time;
                    min_remain_idx=i;
                    
                }
    
            }

            if (min_remain_idx==-1) {
                executed_timeline[current_time]=NULL;
                current_time++;
                continue;
            } 

            Process *curr_p=&processes_copy[min_remain_idx];
            
            if (curr_p->remaining_time==curr_p->cpu_burst_time) {
                curr_p->start_time=current_time;
            }

            curr_p->remaining_time--;
            executed_timeline[current_time]=curr_p;

            current_time++;
            if (curr_p->remaining_time==0) {

                num_completed++;

                curr_p->is_completed=true;
                curr_p->complete_time=current_time;
                curr_p->turnaround_time=curr_p->complete_time-curr_p->arrival_time;
                curr_p->waiting_time=curr_p->turnaround_time-curr_p->cpu_burst_time;
            }

    
        }
    
        // 간트 차트
        // printf("Preemptive SJF Gantt Chart:\n");
        // int curr_pid=executed_timeline[0] ? executed_timeline[0]->pid : -1;
        // for (int i=0; i<current_time; i++) {
            
        //     if(i==0 || executed_timeline[i]->pid!=curr_pid) {
        //         if (executed_timeline[i]==NULL) {
        //             printf("IDLE (%d~",i);
        //         }  
        //         else {
        //             printf("PID %d (%d~",executed_timeline[i]->pid,i);
        //         }
        //         curr_pid=executed_timeline[i]->pid;
                
        //     }
        //     if (i == current_time - 1 || curr_pid == executed_timeline[i + 1]) {
        //         printf("%d) | ", i + 1);
        //     }


        // }

        printf("Preemptive SJF Gantt Chart:\n| ");

        for (int i = 0; i < current_time; i++) {
            if (i == 0 || executed_timeline[i] != executed_timeline[i - 1]) {
                if (executed_timeline[i] == NULL) {
                    printf("IDLE (%d~", i);
                } else {
                    printf("PID %d (%d~", executed_timeline[i]->pid, i);
                }
            }

            if (i == current_time - 1 || executed_timeline[i] != executed_timeline[i + 1]) {
                printf("%d) | ", i + 1);
            }
        }

        printf("\n");
    
        // 성능 분석
        evaluate(processes_copy, num_process, "Preemptive SJF");

}

void pre_priority(Process *processes, int num_process) {

        // 복사
        Process processes_copy[MAX_PROCESS];
        memcpy(processes_copy, processes, sizeof(Process)*num_process);
    
        // 시간별 실행된 프로세스 저장
        Process *executed_timeline[MAX_TIME];
    
        int current_time=0;
        int num_completed=0;
    
        while(num_completed < num_process){

            if (current_time >= MAX_TIME*10) {
                printf("ERROR: current_time exceeded MAX_TIME (%d)\n", MAX_TIME*10);
                exit(1);  // 또는 break;
            }
    
            int min_priority_idx=-1;
            int min_priority=num_process+1;
            // bool is_preempted=false;
            
            for (int i=0; i<num_process; i++) {
                if (processes_copy[i].arrival_time > current_time){
                    continue;
                }
    
                // 현재 시점에서 priority가 작은 것 선택, 만약에 같다면 먼저 도착한 것으로
                if(!processes_copy[i].is_completed && (processes_copy[i].priority < min_priority ||
                    (processes_copy[i].priority == min_priority &&
                     processes_copy[i].arrival_time < processes_copy[min_priority_idx].arrival_time))) {
    
                    min_priority = processes_copy[i].priority;
                    min_priority_idx=i;
                    
                }
    
            }

            if (min_priority_idx==-1) {
                executed_timeline[current_time]=NULL;
                current_time++;
                continue;
            } 

            Process *curr_p=&processes_copy[min_priority_idx];
            
            if (curr_p->remaining_time==curr_p->cpu_burst_time) {
                curr_p->start_time=current_time;
            }

            curr_p->remaining_time--;
            executed_timeline[current_time]=curr_p;
            
            current_time++;

            if (curr_p->remaining_time==0) {

                num_completed++;

                curr_p->is_completed=true;
                curr_p->complete_time=current_time;
                curr_p->turnaround_time=curr_p->complete_time-curr_p->arrival_time;
                curr_p->waiting_time=curr_p->turnaround_time-curr_p->cpu_burst_time;
            }
    
        }

        printf("Preemptive Priority Gantt Chart:\n| ");

        for (int i = 0; i < current_time; i++) {
            if (i == 0 || executed_timeline[i] != executed_timeline[i - 1]) {
                if (executed_timeline[i] == NULL) {
                    printf("IDLE (%d~", i);
                } else {
                    printf("PID %d (%d~", executed_timeline[i]->pid, i);
                }
            }

            if (i == current_time - 1 || executed_timeline[i] != executed_timeline[i + 1]) {
                printf("%d) | ", i + 1);
            }
        }

        printf("\n");
    
        // 성능 분석
        evaluate(processes_copy, num_process, "Preemptive Priority");

}

void round_robin(Process *processes, int num_process) {
    Process processes_copy[MAX_PROCESS];
    memcpy(processes_copy, processes, sizeof(Process) * num_process);
    
    Process *executed_timeline[MAX_TIME];
    bool enqueued[MAX_PROCESS] = { false };

    int current_time=0;
    int num_completed=0;

    Queue ready_queue;
    init_queue(&ready_queue);

    while(num_completed < num_process ) {
        
        // ==
        for (int i=0; i<num_process; i++) {
            if (processes_copy[i].arrival_time == current_time &&!enqueued[i]) {
                if (is_full(&ready_queue)) {
                    printf("full");
                }
                enqueue(&ready_queue, &processes_copy[i]);
                enqueued[i]=true;
            }
        }

        if (is_empty(&ready_queue)) {
            printf("empty");
            executed_timeline[current_time]=NULL;
            current_time++;
            continue;
        }

        Process *curr_p = dequeue(&ready_queue);

        if (curr_p->remaining_time == curr_p->cpu_burst_time) {
            curr_p->start_time = current_time;
        }

        int time_quantum=TIME_QUANTUM;
        while(time_quantum>0 && curr_p->remaining_time>0){
            executed_timeline[current_time]=curr_p;
            time_quantum--;
            curr_p->remaining_time--;
            // current_time++;

            // ==
            for (int i = 0; i < num_process; i++) {
                if (processes_copy[i].arrival_time == current_time) {
                    if (is_full(&ready_queue)) {
                        printf("full");
                    }
                    enqueue(&ready_queue, &processes_copy[i]);
                    enqueued[i]=true;
                }
            }

            current_time++;
        }

        // current_time++;

        if (curr_p->remaining_time==0 && !curr_p->is_completed){

            num_completed++;
            curr_p->is_completed=true;
            curr_p->complete_time=current_time;
            curr_p->turnaround_time=curr_p->complete_time-curr_p->arrival_time;
            curr_p->waiting_time=curr_p->turnaround_time-curr_p->cpu_burst_time;
        }
        else {
            // if (is_full(&ready_queue)){
            //     printf("full");
            // }
            enqueue(&ready_queue,curr_p);
            // current_time++;
        }

        // current_time++;

    }

    // printf("%d",current_time);

    printf("Round Robin Gantt Chart:\n| ");
    

        for (int i = 0; i < current_time; i++) {
            if (i == 0 || executed_timeline[i] != executed_timeline[i - 1]) {
                if (executed_timeline[i] == NULL) {
                    printf("IDLE (%d~", i);
                } else {
                    printf("PID %d (%d~", executed_timeline[i]->pid, i);
                }
            }

            if (i == current_time - 1 || executed_timeline[i] != executed_timeline[i + 1]) {
                printf("%d) | ", i + 1);
            }
        }

        printf("\n");
    
        // 성능 분석
        evaluate(processes_copy, num_process, "Round Robin");


}