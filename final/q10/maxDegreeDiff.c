
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
int numInEdge(Graph g, int v);
int numOutEdge(Graph g, int v);

int maxDegreeDiff(Graph g) {
    int max = 0;
    for (int i = 0; i < GraphNumVertices(g); i ++) {
        int diff = numInEdge(g, i) - numOutEdge(g, i); 
        if (diff < 0) {
            diff = diff * -1;
        }
        if (max == 0) {
            max = diff;
        } else {
            if (diff > max) {
                max = diff;
            }
        }
    }
    return max;
}

int numInEdge(Graph g, int v) {
    int num = 0;
    for (int i = 0; i < GraphNumVertices(g); i ++) {
        struct adjNode *w = g->edges[i];
        while (w != NULL) {
            if (w->v == v) {
                num ++;
            }
            w = w->next;
        }

    }
    return num;
}

int numOutEdge(Graph g, int v) {
    int num = 0;
    struct adjNode *w = g->edges[v];
    while (w != NULL) {
        num ++;
        w = w->next;
    }
    return num;
}