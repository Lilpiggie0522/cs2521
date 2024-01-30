
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	int nV = GraphNumVertices(g);
	int *pred = malloc(sizeof(int) * nV);
	for (int i = 0; i < nV; i ++) {
		pred[i] = -1;
	}

	Queue q = QueueNew();
	pred[src] = src;
	QueueEnqueue(q, src);
	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);  
		for (int w = 0; w < nV; w ++) {
			if (GraphIsAdjacent(g, v, w) && pred[w] == -1) {
				pred[w] = v;
				if (w == dest) {
					break;
				}
				QueueEnqueue(q, w);
			}
		}
	}

	int w = dest;
	int counter = 0;
	while (w != src) {
		w = pred[w];
		if (w == -1) {
			free(pred);
			QueueFree(q);
			return -1;
		}
		counter ++;
	}
	free(pred);
	QueueFree(q);
	return counter;
}

