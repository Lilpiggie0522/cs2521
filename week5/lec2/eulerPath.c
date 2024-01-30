
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphPrivate.h"

static bool hasEulerPath(Graph g);
static int degree(Graph g, Vertex v);
static bool eulerConnected(Graph g);
static void dfsRec(Graph g, Vertex v, bool *visited);

int main(void) {
	Graph g = GraphRead(stdin);
	
	printf("Graph:\n");
	GraphShow(g);

	bool answer = hasEulerPath(g);
	printf("The graph %s an Euler path\n",
			answer ? "has" : "does not have");

	GraphFree(g);
}

static bool hasEulerPath(Graph g) {
	int numOddDegree = 0;
	for (Vertex v = 0; v < g->nV; v ++) {
		if (degree(g, v) % 2 != 0) {
			numOddDegree ++;
		}
	}

	return (numOddDegree == 0 || numOddDegree == 2) && (eulerConnected(g));
}

int degree(Graph g, Vertex v) {
	struct adjNode *curr = g->edges[v];
	int deg = 0;
	while (curr != NULL) {
		deg ++;
		curr = curr->next;
	}
	return deg;
}

bool eulerConnected(Graph g) {
	bool *visited = malloc(sizeof(bool) * g->nV);
	for (int i = 0; i < g->nV; i ++) {
		visited[i] = false;
	}
	for (Vertex v = 0; v < g->nV; v ++) {
		if (degree(g, v) > 0) {
			dfsRec(g, v, visited);
			break;
		}
	}
	for (Vertex v = 0; v < g->nV; v ++) {
		if ((degree(g, v) > 0) && (visited[v] == false)) {
			free(visited);
			return false;
		}
	}
	free(visited);
	return true;
}

void dfsRec(Graph g, Vertex v, bool *visited) {
	visited[v] = true;
	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (!visited[w]) {
			dfsRec(g, w, visited);
		}
	}
}








/* static bool hasEulerPath(Graph g) {
	int numOddDegree = 0;
	for (Vertex v = 0; v < g->nV; v++) {
		if (degree(g, v) % 2 == 1) {
			numOddDegree++;
		}
	}

	return (numOddDegree == 0 || numOddDegree == 2) &&
		eulerConnected(g);
}

static int degree(Graph g, Vertex v) {
	int deg = 0;
	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		deg++;
	}
	return deg;
}

static bool eulerConnected(Graph g) {
	bool *visited = calloc(g->nV, sizeof(bool));

	for (Vertex v = 0; v < g->nV; v++) {
		if (degree(g, v) > 0) {
			dfsRec(g, v, visited);
			break;
		}
	}

	for (Vertex v = 0; v < g->nV; v++) {
		if (degree(g, v) > 0 && !visited[v]) {
			return false;
		}
	}

	return true;
}

static void dfsRec(Graph g, Vertex v, bool *visited) {
	visited[v] = true;

	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (!visited[w]) {
			dfsRec(g, w, visited);
		}
	}
}
 */