
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
void dfsRec(Graph g, int v, bool *visited, int *pred);

void depthFirstSearch(Graph g, int src) {
	bool *visited = malloc(sizeof(bool) * GraphNumVertices(g));
	int *pred = malloc(sizeof(int) * GraphNumVertices(g));
	for (int i = 0; i < GraphNumVertices(g); i ++) {
		visited[i] = false;
		pred[i] = -1;
	}
	dfsRec(g, src, visited, pred);
	// for (int i = 0; i < GraphNumVertices(g); i ++) {
	// 	printf("%d ", pred[i]);
	// }
	free(visited);
	free(pred);
}

void dfsRec(Graph g, int v, bool *visited, int *pred) {
	visited[v] = true;
	printf("%d ", v);
	for (int i = 0; i < GraphNumVertices(g); i ++) {
		int w = i;
		if (GraphIsAdjacent(g, v, w)) {
			if (visited[w] == false) {
				pred[w] = v;
				dfsRec(g, w, visited, pred);
			}
		}
	}
}