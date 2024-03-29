
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphPrivate.h"
#include "Queue.h"

// void bfs(Graph g, Vertex src) {
// 	// bool *visited = calloc(g->nV, sizeof(bool));
// 	int *predecessor = malloc(g->nV * sizeof(int));
// 	Queue q = QueueNew();

// 	for (int i = 0; i < g->nV; i++) {
// 		predecessor[i] = -1;
// 	}

// 	printf("BFS visit order: %d ", src);
// 	// visited[src] = true;
// 	QueueEnqueue(q, src);
// 	predecessor[src] = src;
// 	while (QueueSize(q) > 0) {
// 		Vertex v = QueueDequeue(q);
// 		struct adjNode *curr = g->edges[v];
// 		for (; curr != NULL; curr = curr->next) {
// 			Vertex w = curr->v;
// 			if (predecessor[w] == -1) {
// 				printf("%d ", w);
// 				// visited[w] = true;
// 				predecessor[w] = v;
// 				QueueEnqueue(q, w);
// 			}
// 		}
// 	}

// 	printf("\n");
// 	for (int i = 0; i < g->nV; i++) {
// 		printf("Predecessor of %d is %d\n", i, predecessor[i]);
// 	}

// 	// free(visited);
// 	free(predecessor);
// 	QueueFree(q);
// }

// void findPathBfs(Graph g, Vertex src, Vertex dest) {
// 	bool *visited = calloc(g->nV, sizeof(bool));
// 	int *predecessor = malloc(g->nV * sizeof(int));
// 	Queue q = QueueNew();

// 	for (int i = 0; i < g->nV; i++) {
// 		predecessor[i] = -1;
// 	}

// 	visited[src] = true;
// 	QueueEnqueue(q, src);

// 	while (QueueSize(q) > 0) {
// 		Vertex v = QueueDequeue(q);
// 		struct adjNode *curr = g->edges[v];
// 		for (; curr != NULL; curr = curr->next) {
// 			Vertex w = curr->v;
// 			if (!visited[w]) {
// 				visited[w] = true;
// 				predecessor[w] = v;
// 				QueueEnqueue(q, w);
// 			}
// 		}
// 	}

// 	if (predecessor[dest] != -1) {
// 		printf("Path from %d to %d: ", src, dest);
// 		Vertex v = dest;
// 		while (v != src) {
// 			printf("%d -> ", v);
// 			v = predecessor[v];
// 		}
// 		printf("%d\n", src);
// 	} else {
// 		printf("No path from %d to %d\n", src, dest);
// 	}

// 	free(visited);
// 	free(predecessor);
// 	QueueFree(q);
// }

void bfs(Graph g, Vertex src) {
	int *predecessor = malloc(sizeof(int) * g->nV);
	for (int i = 0; i < g->nV; i ++) {
		predecessor[i] = -1;
	}

	Queue q = QueueNew();
	QueueEnqueue(q, src);
	predecessor[src] = src;
	while (QueueSize(q) > 0) {
		Vertex v = QueueDequeue(q);
		printf("visiting order is %d\n", v);
		struct adjNode *curr = g->edges[v];
		for (; curr != NULL; curr = curr->next) {
			Vertex w = curr->v;
			if (predecessor[w] == -1) {
				QueueEnqueue(q, w);
				predecessor[w] = v;
			}
		}
	}
	for (int i = src; i < g->nV; i ++) {
		printf("predecessor for %d is %d\n", i, predecessor[i]);
	}
	QueueFree(q);
	free(predecessor);
}

void findPathBfs(Graph g, Vertex src, Vertex dest) {
	int *predecessor = malloc(sizeof(int) * g->nV);
	for (int i = 0; i < g->nV; i ++) {
		predecessor[i] = -1;
	}

	Queue q = QueueNew();
	QueueEnqueue(q, src);
	predecessor[src] = src;
	while (QueueSize(q) > 0) {
		Vertex v = QueueDequeue(q);
		printf("visiting order is %d\n", v);
		struct adjNode *curr = g->edges[v];
		for (; curr != NULL; curr = curr->next) {
			Vertex w = curr->v;
			if (predecessor[w] == -1) {
				QueueEnqueue(q, w);
				predecessor[w] = v;
			}
		}
	}
	for (int i = src; i < g->nV; i ++) {
		printf("predecessor for %d is %d\n", i, predecessor[i]);
	}
	Vertex v = dest;
	printf("going from dest ");
	while (v != src) {
		printf("%d->", v);
		v = predecessor[v];
	}
	printf("%d\n", src);
	QueueFree(q);
	free(predecessor);
}
