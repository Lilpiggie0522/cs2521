#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"



#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

struct graph {
    int nV;
    int nE;
    struct adjNode **edges;
};

struct adjNode {
    struct adjNode *next;
    int v;
};


Graph GraphNew(int nV) {
    Graph g = malloc(sizeof(struct graph));
    g->edges = malloc(nV * sizeof(struct adjNode *));
    for (int i = 0; i < nV; i ++) {
        g->edges[i] = NULL;
    }
    g->nV = nV;
    g->nE = 0;
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
    struct adjNode *current = g->edges[v];
    while (current != NULL) {
        if (current->v == w) {
            return true;
        }
    }
    return false;
}

void GraphInsertEdge(Graph g, Vertex v, Vertex w) {
    struct adjNode *nodeV = malloc(sizeof(struct adjNode));
    nodeV->v = v;
    nodeV->next = NULL;

    struct adjNode *nodeW = malloc(sizeof(struct adjNode));
    nodeW->v = w;
    nodeW->next = NULL;

    struct adjNode *rowVhead = g->edges[v];
    if (rowVhead == NULL) {
        rowVhead = nodeW;
    } else {
        struct adjNode *curr = rowVhead;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = nodeW;
    }
    struct adjNode *rowWhead = g->edges[w];
    if (rowWhead == NULL) {
        rowWhead = nodeV;
    } else {
        struct adjNode *curr = rowWhead;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = nodeV;
    }
    g->nE ++;
}

void GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    
}