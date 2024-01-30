#include <stdlib.h>
#include <stdio.h>
struct queue {
	Stack s1;
	Stack s2;
};

Queue QueueNew(void) {
	Queue q = malloc(sizeof(struct queue));
	q->s1 = StackNew();
	q->s2 = StackNew();
	return q;
}

int main(int argc, char *argv[]) {

    return 0;
}

void QueueEnqueue(Queue q, int item) {
	if (StackSize(q->s1) == 0) {
        StackPush(q->s1, item);
        return;
    }
    while (StackSize(q->s1) != 0) {
        int num = StackPop(q->s1);
        StackPush(q->s2, num);
    }

    StackPush(q->s1, item);
    while (StackSize(q->s2) != 0) {
        int num = StackPop(q->s1);
        StackPush(q->s1, num);
    }
}

int QueueDequeue(Queue q) {
	// TODO
}