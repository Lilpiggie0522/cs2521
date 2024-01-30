
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
void dfsRec(Graph g, int v, int *pred);

int numReachable(Graph g, int src) {
	int nv = GraphNumVertices(g);
	int *pred = malloc(sizeof(int) * nv);
	for (int i = 0; i < nv; i ++) {
		pred[i] = -1;
	}

	dfsRec(g, src, pred);
	int counter = 0;
	for (int i = 0; i < nv; i ++) {
		// printf("%d\n", pred[i]);
		if (pred[i] != -1) {
			counter ++;
		}
	}
	free(pred);
	if (counter == 0) {
		counter ++;
	}
	return counter;
}

void dfsRec(Graph g, int v, int *pred) {
	for (int i = 0; i < GraphNumVertices(g); i ++) {
		if (GraphIsAdjacent(g, v, i) && pred[i] == -1) {
			pred[i] =  v;
			dfsRec(g, i, pred);
		}
	}
}

