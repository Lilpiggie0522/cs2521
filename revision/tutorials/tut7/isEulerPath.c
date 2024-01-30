#include <stdio.h>

bool isEulerPath(Graph g, struct edge e[], int nE) {
    if (nE != g->nE) {
        return false;
    }

    //  check e actually a path
    for (int i = 0; i < nE - 1; i ++) {
        if (e[i].w != e[i + 1].v) {
            return false;
        }
    }

    //  check every edge of e is in g
    for (int i = 0; i < nE; i ++) {
        int row = e[i].v;
        int column = e[i].w;
        if (g->edges[row][column] != true) {
            return false;
        }
    }

    // check exactly once
    for (int i = 0; i < nE; i ++) {
        for (int j = i + 1; j < nE; j ++) {
            if (e[i].v == e[j].v && e[i].w == e[j].w) {
                return false;
            }
            if (e[i].v == e[j].w && e[i].w == e[j].v) {
                return false;
            }
        }
    }
    return true;
}