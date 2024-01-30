#include <stdlib.h>
#include <stdbool.h>


struct queue{
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct queue *Queue;

Queue create_queue();
void Enqueue(Queue q, int value);
bool isEmpty(Queue q);
int Dequeue(Queue q);
void Destroy(Queue q);
struct Node *destroyNodes(struct Node *curr);
int peek(Queue q);
int QueueSize(Queue q);