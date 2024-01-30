
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int numWithin(Graph g, int src, int dist) {
	int size = GraphNumVertices(g);
	int *pred = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i ++) {
		pred[i] = -1;
	}

	Queue q = QueueNew();
	pred[src] = src;
	QueueEnqueue(q, src);
	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);
		for (int w = 0; w < size; w ++) {
			if (pred[w] == -1 && GraphIsAdjacent(g, v, w)) {
				pred[w] = v;
				QueueEnqueue(q, w);
			}
		}
	}
	int final = 0;
	for (int i = 0; i < size; i ++) {
		int away = 0;
		int w = i;
		while (w != src) {
			w =  pred[w];
			if (w == -1) {
				break;
			}
			away ++;
		}
		if (w == src && away <= dist) {
			final ++;
		}
	}
	free(pred);
	QueueFree(q);
	return final;
}


