#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

struct graph {
    int nV;
    int nE;
    bool **edges;
};


Graph GraphNew(int nV) {
    Graph g = malloc(sizeof(struct graph));
    g->nV = nV;
    g->nE = 0;
    g->edges = malloc(sizeof(nV * sizeof(bool *)));
    for (int i = 0; i < nV; i ++) {
        g->edges[i] = malloc(nV * sizeof(bool *));
        for (int j = 0; j < nV; j ++) {
            g->edges[i][j] = 0;
        }
    }
    return g;
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i ++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

int GraphNumberVerticies(Graph g) {
    return g->nV;
}

int GraphNumberEdges(Graph g) {
    return g->nE;
}

bool GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    return g->edges[v][w];
}

void GraphInsertEdge(Graph g, Vertex v, Vertex w) {
    if (g->edges[v][w] != 1) {
        g->edges[v][w] = 1;
        g->edges[w][v] = 1;
        g->nE ++;
    }
}

void GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    if (g->edges[v][w] != 0) {
        g->edges[v][w] = 0;
        g->edges[w][v] = 0;
        g->nE --;
    }
}