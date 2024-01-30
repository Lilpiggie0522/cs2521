// Implementation of the Undirected Weighted Graph ADT
// Uses an adjacency matrix

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Pq.h"

// DO NOT modify this struct
struct graph {
    int nV;         // #vertices
    int nE;         // #edges
    double **edges; // adjacency matrix storing positive weights
                    // 0 if nodes not adjacent
};

static bool validVertex(Graph g, Vertex v);
bool checkPath(Graph g, Vertex v, Vertex w);
bool dfsHasPath(Graph g, Vertex v, Vertex dest, bool *visited);


////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV) {
    assert(nV > 0);
    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    g->edges = malloc(nV * sizeof(double *));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->edges[i] = calloc(nV, sizeof(double));
        if (g->edges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    return g;
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

////////////////////////////////////////////////////////////////////////

int GraphNumVertices(Graph g) {
    return g->nV;
}

bool GraphInsertEdge(Graph g, struct edge e) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    assert(e.v != e.w);
    assert(e.weight > 0.0);

    if (g->edges[e.v][e.w] == 0.0) {
        g->edges[e.v][e.w] = e.weight;
        g->edges[e.w][e.v] = e.weight;
        g->nE++;
        return true;
    } else {
        return false;
    }
}

bool GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (g->edges[v][w] != 0.0) {   // edge e in graph
        g->edges[v][w] = 0.0;
        g->edges[w][v] = 0.0;
        g->nE--;
        return true;
    } else {
        return false;
    }
}

double GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));
    
    return g->edges[v][w];
}

void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int v = 0; v < g->nV; v++) {
        for (int w = v + 1; w < g->nV; w++) {
            if (g->edges[v][w] != 0.0) {
                printf("Edge %d - %d: %lf\n", v, w, g->edges[v][w]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Your task

Graph GraphMst(Graph g) {
    // TODO: Complete this function
    // Initializing empty mst

    Graph mst = GraphNew(g->nV);

    // Using kruskal btw
    // Create pq and add each edge to pq
    Pq pq = PqNew();
    for (int i = 0; i < g->nV; i ++) {
        for (int j = 0; j < g->nV; j ++) {
            if (g->edges[i][j] != 0.0) {
                struct edge e;
                e.v = i;
                e.w = j;
                e.weight = g->edges[i][j];
                PqInsert(pq, e);
            }
        }
    }
    while (!PqIsEmpty(pq)) {
        struct edge sorted = PqExtract(pq);
        Vertex v = sorted.v;
        Vertex w = sorted.w;
        // check path between v and w
        if (!checkPath(mst, v, w)) {
            GraphInsertEdge(mst, sorted);
        }
        
        if (mst->nE == g->nV - 1) {
            PqFree(pq);
            return mst;
        }
    }
    PqFree(pq);
    return NULL;
}

bool checkPath(Graph g, Vertex v, Vertex w) {
    bool *visited = malloc(sizeof(bool) * g->nV);
    for (int i = 0; i < g->nV; i ++) {
        visited[i] = false;
    }
    bool result = dfsHasPath(g, v, w, visited);
    free(visited);
    return result;
}

bool dfsHasPath(Graph g, Vertex v, Vertex dest, bool *visited) {
    visited[v] = true;
    if (v == dest) {
        return true;
    }

    for (Vertex i = 0; i < g->nV; i ++) {
        if (g->edges[v][i] != 0.0) {
            Vertex w = i;
            if (!visited[w]) {
                if (dfsHasPath(g, w, dest, visited)) {
                    return true;
                }
            }
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////

static bool validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}

