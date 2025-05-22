#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include "process.h"

#define MAX_QUEUE_SIZE 10

typedef struct {
    Process *queue[MAX_QUEUE_SIZE];
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
