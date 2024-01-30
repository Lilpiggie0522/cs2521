#include "Graph.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    Graph g = GraphNew(5);
    GraphInsertEdge(g, 2, 4);
    GraphInsertEdge(g, 1, 4);
    GraphInsertEdge(g, 0, 2);
    GraphInsertEdge(g, 2, 1);
    // GraphRemoveEdge(g, 2, 1);
    printf("%d\n", GraphNumberEdges(g));
    return 0;
}