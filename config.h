#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include "process.h"
#include "constants.h"

typedef struct {
    Process *queue[NUM_PROCESS];
    int front;
    int rear;
    int size;
} Queue;

void init_queue(Queue *q);
void enqueue(Queue *q, Process *element);
Process* dequeue(Queue *q);

bool is_empty(Queue *q);
bool is_full(Queue *q);

void print_queue(Queue *q, const char *name);

#endif
