
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int furthestReachable(Graph g, int src) {
	int nv = GraphNumVertices(g);
	int *pred = malloc(sizeof(int) * nv);
	for (int i = 0; i < nv; i ++) {
		pred[i] = -1;
	}
	Queue q = QueueNew();
	pred[src] = src;
	QueueEnqueue(q, src);

	while (!QueueIsEmpty(q)) {
		int v = QueueDequeue(q);
		for (int w = 0; w < nv; w ++) {
			if (GraphIsAdjacent(g, v, w) && pred[w] == -1) {
				pred[w] = v;
				QueueEnqueue(q, w);
			}
		}
	}
	// for (int i = 0; i < nv; i ++) {
	// 	printf("%d\n", pred[i]);
	// }
	int counter = 0;
	int fur = -1;
	bool jump = false;
	for (int i = 0; i < nv; i ++) {
		int w = i;
		int innerC = 0;
		while (w != src) {
			w = pred[w];
			if (w == -1) {
				jump = true;
				break;
			}
			innerC ++;
		}
		if (!jump) {
			if (innerC > counter) {
			counter = innerC;
			
			fur = i;
			} else if (innerC == counter) {
				if (i > fur) {
					fur = i;
				}
			}
		}
		jump = false;
	}
	free(pred);
	QueueFree(q);
	return fur;
}

