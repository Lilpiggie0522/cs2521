
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	int *pred = malloc(sizeof(int) * GraphNumVertices(g));
	for (int i = 0; i < GraphNumVertices(g); i ++) {
		pred[i] = -1;
	}
	Queue q = QueueNew();
	printf("%d ", src);
	pred[src] = src;
	QueueEnqueue(q, src);
	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);
		for (int i = 0; i < GraphNumVertices(g); i ++) {
			int w = i;
			if (GraphIsAdjacent(g, v, i) && pred[w] == -1) {
				printf("%d ", w);
				pred[w] = v;
				QueueEnqueue(q, w);
			}
		}
	}
	QueueFree(q);
	free(pred);
}

