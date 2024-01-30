typedef struct queue *Queue;

void queueNew();
void queue *enqueue(Queue q, int v);
void recursiveEnqueue(struct node *curr, int v);
int deQueue(Queue q);
int queueSize(Queue q);
void queueFree(Queue q);
void freeNodes(struct node *curr);