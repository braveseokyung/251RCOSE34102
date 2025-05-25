#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int cpu_burst_time;
    int io_burst_time;
    int io_request_time;
    int priority;

    int start_time;
    int waiting_time;
    int complete_time;
    int turnaround_time;

    bool is_completed;
} Process;

void create_process(Process *processes, int num_process, int seed);

#endif