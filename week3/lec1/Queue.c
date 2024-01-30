/// Queue implementation using array
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define MAX_SIZE 50

struct queue {
    Item *head;
    Item size;
};

struct node {
    Item value;
    struct node *next;
};

Queue QueueNew(void) {
    Queue new = malloc(sizeof(struct queue));
    new->head = malloc(sizeof(int) * MAX_SIZE);
    new->size = 0;
    return new;
}

void QueueFree(Queue q) {
    free(q->head);
}

void QueueEnqueue(Queue q, Item value) {
    (q->head)[q->size] = value;
    q->size ++;
}

void QueueDequeue(Queue q) {
    q->head = &((q->head)[1]);
    q->size --;
    q->head = realloc(q->head, q->size);
}

Item QueueSize(Queue q) {
    return q->size;
}

Item QueuePeek(Queue q) {
    return (q->head)[0];
}