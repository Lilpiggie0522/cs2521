#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "Queue.h"

struct Node {
    int value;
    struct Node *next;
};

int main(int argc, char **argv[]) {
    Queue q = create_queue();
    printf("q size is %d\n", q->size);
    Enqueue(q, 3);
    Enqueue(q, 2);
    Enqueue(q, 1);
    Enqueue(q, 9);
    Dequeue(q);
    
    printf("q head is %d, tail is %d\n", q->head->value, q->tail->value);
    printf("is queue empty? %d\n", isEmpty(q));
    printf("peek is %d\n", peek(q));
    printf("dequeue is %d\n", Dequeue(q));
    printf("q size is %d\n", QueueSize(q));
    Destroy(q);
    return 0;
    
}

Queue create_queue() {
    Queue new_q = malloc(sizeof(struct queue));
    new_q->head = NULL;
    new_q->tail = NULL;
    new_q->size = 0;
    return new_q;
}

int QueueSize(Queue q) {
    return q->size;
}

bool isEmpty(Queue q) {
    return q->size == 0;
}

int peek(Queue q) {
    return q->head->value;
}

void Enqueue(Queue q, int value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->next = NULL;
    if (isEmpty(q)) {
        q->head = new_node;
        q->tail = new_node;
        q->size ++;
        return;
    }
    q->tail->next = new_node;
    q->tail = new_node;
    q->size ++;
    return;
}

int Dequeue(Queue q) {
    struct Node *old = q->head;
    int value = old->value;
    q->head = q->head->next;
    free(old);
    q->size --;
    return value;
}

void Destroy(Queue q) {
    destroyNodes(q->head);
    free(q);
}


struct Node *destroyNodes(struct Node *curr) {
    if (curr == NULL) {
        return curr;
    }
    curr->next = destroyNodes(curr->next);
    free(curr);
}