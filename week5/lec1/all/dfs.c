
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphPrivate.h"


struct stack {
	int size;
	struct node *head;
};

struct node {
	int v;
	struct node *next;
};


static void dfsRec(Graph g, Vertex v, bool *visited);
static void push(struct stack *s, int v);
static int pop(struct stack *s);
static int stackSize(struct stack *s);
static void freeStack(struct stack *s);
bool dfsHasPath(Graph g, Vertex src, Vertex dest, bool *visited);
void findPath(Graph g, Vertex src, Vertex dest);
bool dfsFindPath(Graph g, Vertex src, Vertex dest, int *predecessor);
/* void dfs(Graph g, Vertex src) {
	bool *visited = calloc(g->nV, sizeof(bool));
	printf("DFS visit order: ");
	dfsRec(g, src, visited);
	printf("\n");
	free(visited);
}

static void dfsRec(Graph g, Vertex v, bool *visited) {
	printf("%d ", v);
	visited[v] = true;

	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (!visited[w]) {
			dfsRec(g, w, visited);
		}
	}
} */

void dfs(Graph g, Vertex src) {
	bool *visited = malloc(sizeof(bool) * g->nV);
	for (int i = 0; i < g->nV; i ++) {
		visited[i] = false;
	}
	printf("visiting order is: ");
	dfsRec(g, src, visited);
	printf("\n");
	free(visited);
}

void dfsRec(Graph g, Vertex v, bool *visited) {
	printf("%d ", v);
	visited[v] = true;
	struct adjNode *curr = g->edges[v];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (!visited[w]) {
			dfsRec(g, w, visited);
		}
	}
}

bool hasPath(Graph g, Vertex src, Vertex dest) {
	bool *visited = malloc(sizeof(bool) * g->nV);
	for (int i = 0; i < g->nV; i ++) {
		visited[i] = false;
	}

	bool result = dfsHasPath(g, src, dest, visited);
	free(visited);
	return result;
}

bool dfsHasPath(Graph g, Vertex src, Vertex dest, bool *visited) {
	visited[src] = true;
	if (src == dest) {
		return true;
	}
	struct adjNode *curr = g->edges[src];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (!visited[w]) {
			return dfsHasPath(g, w, dest, visited);
		}
	}
	return false;
}

void findPath(Graph g, Vertex src, Vertex dest) {
	int *predecessor = malloc(sizeof(int) * g->nV);
	for (int i = 0; i < g->nV; i ++) {
		predecessor[i] = -1;
	}
	predecessor[src] = src;
	bool result = dfsFindPath(g, src, dest, predecessor);
	if (result) {
		Vertex v = dest;
		printf("path is <-%d", dest);
		while (v != src) {
			v = predecessor[v];
			printf("<-%d", v);
		}
	}
	free(predecessor);
}

bool dfsFindPath(Graph g, Vertex src, Vertex dest, int *predecessor) {
	if (src == dest) {
		// predecessor[dest] = src;
		return true;
	}
	struct adjNode *curr = g->edges[src];
	for (; curr != NULL; curr = curr->next) {
		Vertex w = curr->v;
		if (predecessor[w] == -1) {
			predecessor[w] = src;
			return dfsFindPath(g, w, dest, predecessor);
		}
	}
	return false;
}












void dfsIter(Graph g, Vertex src) {
	bool *visited = malloc(g->nV * sizeof(bool));
	int *predecessor = malloc(g->nV * sizeof(int));
	for (int i = 0; i < g->nV; i ++) {
		visited[i] = false;
		predecessor[i] = -1;
	}
	struct stack *s = malloc(sizeof(struct stack));
	s->size = 0;
	s->head = NULL;
	push(s, src);
	while (stackSize(s)) {
		Vertex v = pop(s);
		if (!visited[v]) {
			visited[v] = true;
			printf("%d\n", v);
			struct adjNode *curr = g->edges[v];
			for (; curr != NULL; curr = curr->next) {
				Vertex w = curr->v;
				if (!visited[w]) {
					predecessor[w] = v;
					push(s, w);
				}
			}
		}
	}
	freeStack(s);
	free(visited);
	free(predecessor);
}

static void push(struct stack *s, int v) {
	if (s->head == NULL) {
		struct node *new = malloc(sizeof(struct node));
		new->v = v;
		new->next = NULL;
		s->head = new;
		s->size ++;
		return;
	}
	struct node *new = malloc(sizeof(struct node));
	new->v = v;
	new->next = s->head;
	s->size ++;
	s->head = new;
	return;
}

static int pop(struct stack *s) {
	struct node *new = s->head->next;
	int num = s->head->v;
	free(s->head);
	s->size --;
	s->head = new;
	return num;
}

static int stackSize(struct stack *s) {
	if (s == NULL) {
		return 0;
	}
	return s->size;
}

static void freeStack(struct stack *s) {
	struct node *delete = s->head;
	struct node *curr = s->head;
	while (curr != NULL) {
		delete = curr;
		curr = curr->next;
		free(delete);
	}
	free(s);
}



