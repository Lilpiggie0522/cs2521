#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Graph.h"

int dayTrip(Graph g, Vertex s, Vertex vs[]) {
    int nV = g->nV;
    for (int w = 0; w < nV; w ++) {
        if (g->stdEdges[s][w]) {
            vs[w] = 1;
        }
    }

    for (int w = 0; w < nV; w ++) {
        if (g->fastEdges[s][w]) {
            vs[w] = 1;
            for (int j = 0; j < nV; j ++) {
                if (g->fastEdges[w][j]) {
                    vs[j] = 1;
                }
            }
        }
    }

    int num = 0;
    for (int i = 0; i < nV; i ++) {
        if (vs[i] == 1) {
            vs[num] = i;
            num ++;
        }
    }
    return num;
}

// bool vSetNotEmpty(Graph g, int *vSet);
// int findMinimal(Graph g, int *dist, int *vSet);
// void relax(int v, int w, int weight, int *dist);

// int dayTrip(Graph g, Vertex s, Vertex vs[]) {
//     int *dist = malloc(sizeof(int) * g->nV);
//     int *vSet = malloc(sizeof(int) * g->nV);
//     for (int i = 0; i < g->nV; i ++) {
//         dist[i] = INT_MAX;
//         vSet[i] = i;
//     }
//     dist[s] = 0;
//     while (vSetNotEmpty(g, vSet)) {
//         int v = findMinimal(g, dist, vSet);
//         // printf("v is %d\n", v);
//         for (int w = 0; w < g->nV; w ++) {
//             if (g->stdEdges[v][w]) {
//                 int weight = 1;
//                 relax(v, w, weight, dist);
//             }
//         }
//     }
//     int num = 0;
//     for (int i = 0; i < g->nV; i ++) {
//         if (dist[i] <= 1) {
//             vs[num] = i;
//             num ++;
//         }
//     }
//     free(dist);
//     free(vSet);
//     return num;
// }

// bool vSetNotEmpty(Graph g, int *vSet) {
//     int i = 0;
//     for (; i < g->nV; i ++) {
//         if (vSet[i] != -1) {
//             return true;
//         }
//     }
//     return false;
// }

// int findMinimal(Graph g, int *dist, int *vSet) {
//     int min = -1;
//     for (int i = 0; i < g->nV; i ++) {
//         if (vSet[i] != -1) {
//             min = i;
//             break;
//         }
//     }

//     for (int i = 0; i < g->nV; i ++) {
//         if (vSet[i] != -1 && (dist[i] < dist[min])) {
//             min = i;
//         }
//     }
//     if (min != -1) {
//         vSet[min] = -1;
//         // printf("min is %d\n", min);
//         return min;
//     }
//     return min;
// }

// void relax(int v, int w, int weight, int *dist) {
//     if (dist[v] + weight < dist[w]) {
//         dist[w] = dist[v] + weight;
//     }
// }