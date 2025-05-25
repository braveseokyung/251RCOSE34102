#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "config.h"

void init_queue(Queue *q) {

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    
}

void enqueue(Queue *q, Process *element) {
    if (is_full(q)) {
        printf("Queue is full!");
        return;
    }
    q->rear = (q->rear + 1) % NUM_PROCESS;
    q->queue[q->rear]=element;
    q->size++;
    printf("Enqueued PID %d at position %d\n", element->pid, q->rear);
}

Process* dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is empty!");
        return NULL;
    }
    Process *p = q->queue[q->front];
    printf("Dequeued PID %d at position %d\n", p->pid, q->front);

    q->front=(q->front+1) % NUM_PROCESS;
    q->size--;
   
    
    return p;

}

bool is_empty(Queue *q) {
    return q->size==0;
}

bool is_full(Queue *q) {
    return q->size==NUM_PROCESS;
}

void print_queue(Queue *q, const char *name) { 
    printf("Printing %s queue...\n", name);
    printf("Queue size : %d\n", q->size);
    for (int i=0; i < q->size; i++) {
        int idx = (q->front + i) % NUM_PROCESS;
        printf("PID %d |", q->queue[idx]->pid);
    }
    printf("\n");
}