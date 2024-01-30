#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"


struct graph {
    int nV;
    int nE;
    struct adjNode **edges;
};

struct adjNode {
    int v;
    struct adjNode *next;
};

int main (int argc, char *argv[]) {
    Graph g = malloc(sizeof(struct graph));
    g->nV = 4;
    g->edges = malloc(sizeof(struct adjNode *) * g->nV);
    for (int i = 0; i < 4; i ++) {
        g->edges[i] = NULL;
    }
    
}

void bfs(Graph g, Vertex src) {
    bool *visited = malloc(g->nV *sizeof(bool));
    int *predecessor = malloc(g->nV * sizeof(int));
    Queue q = queueNew();

    for (int i = 0; i < g->nV; i ++) {
        visited[i] = false;
        predecessor[i] = -1;
    }
    visited[src] = true;
    enqueue(q, src);
    while (queueSize(q) > 0) {
        Vertex v = dequeue(q);
        for (struct adjNode *curr = g->edges[v]; curr != NULL; curr = curr->next) {
            Vertex w = curr->v;
            if (!visited[w]) {
                visited[w] = true;
                predecessor[w] = v;
                enqueue(q, w);
            }
        }
    }
    for (int i = 0; i < g->nV; i ++) {
        printf("%d\n", predecessor[i]);
    }
    free(visited);
    free(predecessor);
    queueFree(q);
}

void insertEdge(Graph g, int v, int w) {
    g->edges[v] = malloc(sizeof(struct adjNode *));
    g->edges[v]->v = w;
    g->edges[v]->next = NULL;

    g->edges[w] = malloc(sizeof(struct adjNode *));
    g->edges[w]->v = v;
    g->edges[w]->next = NULL;
}