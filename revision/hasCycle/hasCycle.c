
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"
static bool dfsHasCycle(Graph g, int v, int prev, bool *visited);

bool hasCycle(Graph g) {
	int nv = GraphNumVertices(g);
	bool *visited = malloc(sizeof(bool) * nv);
	for (int i = 0; i < nv; i ++) {
		visited[i] = false;
	}

	for (int i = 0; i < nv; i ++) {
		if (visited[i] == false) {
			if (dfsHasCycle(g, i, i, visited)) {
				free(visited);
				return true;
			}
		}
	}
	free(visited);
	return false;
}

static bool dfsHasCycle(Graph g, int v, int prev, bool *visited) {
	visited[v] = true;
	for (int i = 0; i < GraphNumVertices(g); i ++) {
		if (GraphIsAdjacent(g, v, i)) {
			if (i == prev) {
				continue;
			}
			if (visited[i] == true) {
				// printf("v is %d\n", v);
				// printf("i is %d\n", i);
				// printf("prev is %d\n", prev);
				return true;
			} else if (dfsHasCycle(g, i, v, visited) == true) {
				return true;
			}
		}
	}
	return false;
}