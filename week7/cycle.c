
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Graph.h"
#include "GraphPrivate.h"

struct vSet {
	int size;
	int *arr;
};

static bool hasCycle(Graph g);

static bool dfsHasCycle(Graph g, Vertex v, bool *visited, bool *onStack);
int *dijkstraSSSP(Graph g, Vertex src);
void findRemove(struct vSet *vSet, int *dist, int size);
void relax(Vertex v, Vertex w, int *dist, int weight, int *pred);

int main(void) {
	Graph g = GraphRead(stdin);
	
	printf("Graph:\n");
	GraphShow(g);
	dijkstraSSSP(g, 0);
	bool answer = hasCycle(g);
	printf("The graph %s a cycle\n",
			answer ? "contains" : "does not contain");

	
	GraphFree(g);
}

static bool hasCycle(Graph g) {
	bool *visited = calloc(g->nV, sizeof(bool));
	bool *onStack = calloc(g->nV, sizeof(bool));

	for (Vertex v = 0; v < g->nV; v++) {
		if (!visited[v] && dfsHasCycle(g, v, visited, onStack)) {
			free(visited);
			return true;
		}
	}

	free(visited);
	free(onStack);
	return false;
}

static bool dfsHasCycle(Graph g, Vertex v, bool *visited, bool *onStack) {
	visited[v] = true;
	onStack[v] = true;
	printf("Recursed into %d\n", v);

	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (onStack[w]) {
			printf("%d is on the stack - cycle found!\n", w);
			return true;
		} else if (!visited[w]) {
			if (dfsHasCycle(g, w, visited, onStack)) {
				return true;
			}
		}
	}

	printf("Backtracking from %d\n", v);
	onStack[v] = false;
	return false;
}

void dijkstraSSSP(Graph g, Vertex src) {
	int *dist = malloc(sizeof(int) * g->nV);
	int *pred = malloc(sizeof(int) * g->nV);
	

	struct vSet *set = malloc(sizeof(struct vSet));
	set->size = 0;
	set->arr = malloc(sizeof(Vertex) * g->nV);

	for (int i = 0; i < g->nV; i ++) {
		dist[i] = INT_MAX;
		set->arr[i] = i;
		pred[i] = -1;
		set->size ++;
	}
	dist[src] = 0;
	printf("set size is %d\n", set->size);
	while (set->size > 0) {
		// printf("set size is %d\n", set->size);
		// printf("executing loop!\n");
		
		for (Vertex v = 0; v < g->nV; v ++) {
			struct adjNode *curr = g->edges[v];
			while (curr != NULL) {
				// printf("Actually executing relax\n");
				Vertex w = curr->v;
				relax(v, w, dist, curr->weight, pred);
				curr = curr->next;
			}
		}
		findRemove(set, dist, g->nV);
	}

	for (int i = 0; i < g->nV; i ++) {
		printf("pred[%d] is %d\n", i, pred[i]);
	}
}

void findRemove(struct vSet *vSet, int *dist, int size) {
	int minV = 0;
	for (int i = 0; i < size; i ++) {
		if (vSet->arr[i] != - 1) {
			minV = i;
			break;
		}
	}
	for (int i = 0; i < size; i ++) {
		if ((vSet->arr[i] != -1) && dist[i] < dist[minV]) {
			minV = i;
		}
	}
	vSet->arr[minV] = -1;
	vSet->size --;
	// printf("actually deleting size!\n");
	
}

void relax(Vertex v, Vertex w, int *dist, int weight, int *pred) {
	if (dist[v] + weight < dist[w]) {
		dist[w] = dist[v] + weight;
		pred[w] = v;
		// printf("executed relax to w %d\n", w);
	}
}