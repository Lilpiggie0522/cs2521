#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

struct queue {
    int size;
    struct node *head;
    struct node *tail;
};

struct node {
    int v;
    struct adjNode *next;
};


struct queue *queueNew() {
    Queue q = malloc(sizeof(struct queue));
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void queue *enqueue(Queue q, int v) {
    if (q->head == NULL) {
        struct node *new = malloc(sizeof(struct node));
        new->v = v;
        new->next = NULL;
        q->head = new;
    }
    recursiveEnqueue(q->head, v);
    q->size ++;
}

void recursiveEnqueue(struct node *curr, int v) {
    if (curr->next == NULL) {
        struct node *new = malloc(sizeof(struct node));
        new->v = v;
        new->next = NULL;
        curr->next = new;
        return;
    }
    recursiveEnqueue(curr->next, v);
}

int deQueue(Queue q) {
    if (q->head == NULL) {
        return NULL;
    }
    int delete = q->head->v;
    struct node *old = q->head;
    q->head = q->head->next;
    free(old);
    q->size --;
    return delete;
}

int queueSize(Queue q) {
    return q->size;
}

void queueFree(Queue q) {
    if (q == NULL) {
        return;
    }
    freeNodes(q->head);
    free(q);
}

void freeNodes(struct node *curr) {
    if (curr == NULL) {
        return;
    }
    freeNodes(curr->next);
    free(curr);
}