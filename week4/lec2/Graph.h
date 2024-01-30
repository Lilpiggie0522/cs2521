#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef int Vertex;
typedef struct graph *Graph;

Graph GraphNew(int nV);

void GraphFree(Graph g);

int GraphNumberVerticies(Graph g);

int GraphNumberEdges(Graph g);

bool GraphIsAdjacent(Graph g, Vertex v, Vertex w);

void GraphInsertEdge(Graph g, Vertex v, Vertex w);

void GraphRemoveEdge(Graph g, Vertex v, Vertex w);

#endif