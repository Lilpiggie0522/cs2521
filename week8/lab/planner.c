// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "place.h"
#include "Pq.h"
int computeWeight(struct place place1, struct place place2);
////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid1(struct place cities[], int numCities,
              struct place powerPlant,
              struct powerLine powerLines[]) {
    // TODO: Complete this function

    // add all edges
    // sort all edges
    // inserting into mst
    struct place *citiesWithPowerPlant = malloc(sizeof(struct place) * (numCities + 1));
    int i = 0;
    for (i = 0; i < numCities; i ++) {
        citiesWithPowerPlant[i] = cities[i];
    }
    citiesWithPowerPlant[i] = powerPlant;

    Graph g = GraphNew(numCities + 1);
    for (int i = 0; i < numCities + 1; i ++) {
        for (int j = 0; j < numCities + 1; j ++) {
            if (i != j) {
                struct edge newEdge;
                newEdge.v = i;
                newEdge.w = j;
                newEdge.weight = computeWeight(citiesWithPowerPlant[i], citiesWithPowerPlant[j]);
                GraphInsertEdge(g, newEdge);
            }
        }
    }
    Graph mst = GraphMst(g);
    int powerLineIndex = 0;
    int numVertices = GraphNumVertices(mst);
    for (int i = 0; i < numVertices; i ++) {
        for (int j = 0; j < numVertices; j ++) {
            if (GraphIsAdjacent(mst, i, j) != 0.0) {
                struct powerLine newP;
                newP.p1 = citiesWithPowerPlant[i];
                newP.p2 = citiesWithPowerPlant[j];
                powerLines[powerLineIndex] = newP;
                GraphRemoveEdge(mst, i, j);
                powerLineIndex ++;
            }
        }
    }
    free(citiesWithPowerPlant);
    GraphFree(g);
    GraphFree(mst);
    return powerLineIndex;
}

int computeWeight(struct place place1, struct place place2) {
    int weight = sqrt(pow((place1.x - place2.x), 2) + pow((place1.y - place2.y), 2));
    return weight;
}
////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(struct place cities[], int numCities,
              struct place powerPlants[], int numPowerPlants,
              struct powerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
