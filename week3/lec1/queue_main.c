#include <stdio.h>
#include "Queue.h"

int main(int argc, char *argv[]) {
    Queue q = QueueNew();
    QueueEnqueue(q, 3);
    QueueEnqueue(q, 4);
    QueueEnqueue(q, 5);
    printf("front of queue is %d\n", QueuePeek(q));
    QueueDequeue(q);
    printf("front of queue is %d\n", QueuePeek(q));
    QueueFree(q);
    return 0;
}