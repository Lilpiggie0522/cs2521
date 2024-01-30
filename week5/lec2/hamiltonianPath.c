
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphPrivate.h"

// static bool hasHamiltonianPath(Graph g);

// static bool dfsHamiltonianPath(Graph g, Vertex v, bool *visited, int numVerticesLeft);

static bool hasHamiltonianPath(Graph g);
static bool dfsHamiltonianPath(Graph g, Vertex v, int *visited, int numVertex);

int main(void) {
	Graph g = GraphRead(stdin);
	
	printf("Graph:\n");
	GraphShow(g);

	bool answer = hasHamiltonianPath(g);
	printf("The graph %s a Hamiltonian path\n",
			answer ? "has" : "does not have");

	GraphFree(g);
}

static bool hasHamiltonianPath(Graph g) {
	int *visited = malloc(sizeof(int) * g->nV);
	for (int i = 0; i < g->nV; i ++) {
		visited[i] = false;
	}
	Vertex v = 0;
	int numVertex = g->nV;
	for (v = 0; v < g->nV; v ++) {
		if (dfsHamiltonianPath(g, v, visited, numVertex)) {
			free(visited);
			return true;
		}
	}
	free(visited);
	return false;
}

static bool dfsHamiltonianPath(Graph g, Vertex v, int *visited, int numVertex) {
	visited[v] = true;
	numVertex --;	// decrement has to be here, cannot be in the recursive function, (dfsHamiltonianPath(g, w, visited, numVertex) wont work
	if (numVertex == 0) {
		return true;
	}
	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (!visited[w]) {
			if (dfsHamiltonianPath(g, w, visited, numVertex)) {
				return true;
			}
		}
	}
	visited[v] = false;
	return false;
}



/* static bool hasHamiltonianPath(Graph g) {
	bool *visited = calloc(g->nV, sizeof(bool));

	for (Vertex v = 0; v < g->nV; v++) {
		if (dfsHamiltonianPath(g, v, visited, g->nV)) {
			free(visited);
			return true;
		}
	}

	free(visited);
	return false;
}


static bool dfsHamiltonianPath(Graph g, Vertex v, bool *visited, int numVerticesLeft) {
	visited[v] = true;
	numVerticesLeft--;

	if (numVerticesLeft == 0) {
		return true;
	}

	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (!visited[w]) {
			if (dfsHamiltonianPath(g, w, visited, numVerticesLeft)) {
				return true;
			}
		}
	}

	visited[v] = false;
	return false;
} */




