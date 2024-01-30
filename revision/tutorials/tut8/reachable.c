#include <stdio.h>

Set reachable(Graph g, Vertex src) {
   Set s = SetNew();
   Queue q = QueueNew();
   SetInsert(s, src);
   QueueEnqueue(q, src);

   while (!QueueIsEmpty(q)) {
    int v = QueueDequeue(q);
    for (int w = 0; w < g->nE; w ++) {
        if (g->edges[v][w] && !SetContains(s, w)) {
            QueueEnqueue(q, w);
            SetInsert(s, w);
        }
    }
   }
   QueueFree(q);
   return s;
}