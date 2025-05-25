#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include "config.h"

void fcfs(Process *processes, int num_process);
void nonpre_sjf(Process *processes, int num_process);
void nonpre_priority(Process *processes, int num_process);
void pre_sjf(Process *processes, int num_process);

#endif