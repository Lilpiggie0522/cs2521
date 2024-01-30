typedef struct queue *Queue;
typedef int Item;

Queue QueueNew(void);

void QueueFree(Queue q);

void QueueEnqueue(Queue q, Item value);

void QueueDequeue(Queue q);

Item QueueSize(Queue q);

Item QueuePeek(Queue q);
