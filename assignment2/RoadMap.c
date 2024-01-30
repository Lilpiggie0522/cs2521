#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RoadMap.h"
#include "time.h"
typedef int Vertex;

struct nodeIslandInfo {
	int islandNo;
	char *islandName;
};

struct roadMap {
	int numNodes;
	int numRoads;
	struct adjNode **edges; // [*, *, *]
	bool **tc;
	struct nodeIslandInfo *islandsInfo;
	int *islands;
	int numIslands;
	bool *nodeTrafficLights;
};

struct adjNode {
	Vertex v;
	int travelMinutes;
	struct adjNode *next;
	struct time closedFrom;
	struct time closedUntil;
};

void freeList(RoadMap r, struct adjNode *l);
bool checkMaxRoad(RoadMap map, Vertex node1, Vertex node2);
bool checkAlreadyRoad(RoadMap map, Vertex node1, Vertex node2);
void roadInsertOneWay(RoadMap map, int node1, int node2, int travelMinutes);
struct adjNode *listInsert(struct adjNode *head, int node2, int travelMinutes);

////////////////////////////////////////////////////////////////////////
// Task 1
/* Create a new pointer to RoadMap struct that contains various info abou ta map */
RoadMap RoadMapNew(int numNodes) {
	RoadMap r = malloc(sizeof(struct roadMap));
	if (r == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	r->numNodes = numNodes;
	r->numRoads = 0;
	r->edges = malloc(sizeof(struct adjNode *) * numNodes);
	if (r->edges == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	r->tc = malloc(sizeof(bool *) * numNodes);
	
	if (r->tc == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	r->islandsInfo = malloc(sizeof(struct nodeIslandInfo) * numNodes);
	if (r->islandsInfo == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	r->islands = malloc(sizeof(int) * numNodes);
	if (r->islands == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	r->nodeTrafficLights = malloc(sizeof(bool) * numNodes);
	if (r->nodeTrafficLights == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	for (int i = 0; i < numNodes; i ++) {
		r->edges[i] = NULL;
		r->tc[i] = malloc(sizeof(bool) * numNodes);
		if (r->tc[i] == NULL) {
			fprintf(stderr, "not enough memory!\n");
		}
		for (int j = 0; j < numNodes; j ++) {
			(r->tc)[i][j] = false;
		}
		r->islandsInfo[i].islandName = strdup("(unnamed)");
		r->islands[i] = -1;
		r->nodeTrafficLights[i] = false;
	}
	return r;
}
/* Free the given RoadMap */
void RoadMapFree(RoadMap map) {
	for (Vertex v = 0; v < map->numNodes; v ++) {
		freeList(map, map->edges[v]);
	}
	free(map->edges);
	for (int i = 0; i < map->numNodes; i ++) {
		free(map->tc[i]);
	}
	free(map->tc);
	for (int i = 0; i < map->numNodes; i ++) {
		free(map->islandsInfo[i].islandName);
	}
	free(map->islandsInfo);
	free(map->islands);
	free(map->nodeTrafficLights);
	free(map);
}

/* Return number of nodes that are in the RoadMap */
int RoadMapNumNodes(RoadMap map) {
	return map->numNodes;
}

/* Return number of roads/edges that are in the RoadMap */
int RoadMapNumRoads(RoadMap map) {
	return map->numRoads;
}

/* Add a road/edge between two nodes, either 1 way or two way */
bool RoadMapAddRoad(RoadMap map, int node1, int node2,
                    bool isTwoWay, int travelMinutes) {
	if (!checkMaxRoad(map, node1, node2) && !checkAlreadyRoad(map, node1, node2)) {
		roadInsertOneWay(map, node1, node2, travelMinutes);
		
		if (isTwoWay == true) {
			roadInsertOneWay(map, node2, node1, travelMinutes);
		}
		map->numRoads ++;
		return true;
	}
	return false;
}

/* Get the number of roads/edges that a certain node has */
int RoadMapGetRoadsFrom(RoadMap map, int node, struct road roads[]) {
	int roadIndex = 0;
	struct adjNode *curr = map->edges[node];
	while (curr != NULL) {
		roads[roadIndex].fromNode = node;
		roads[roadIndex].toNode = curr->v;
		roads[roadIndex].travelMinutes = curr->travelMinutes;
		roads[roadIndex].closedFrom = curr->closedFrom;
		roads[roadIndex].closedUntil = curr->closedUntil;
		roadIndex ++;
		curr = curr->next;
	}
	return roadIndex;
}

/* Get the number of roads/edges that can go to a given node */
int RoadMapGetRoadsTo(RoadMap map, int node, struct road roads[]) {
	int roadIndex = 0;
	for (Vertex v = 0; v < map->numNodes; v ++) {
		struct adjNode *curr = map->edges[v];
		while (curr != NULL) {
			if (curr->v == node) {
				roads[roadIndex].fromNode = v;
				roads[roadIndex].toNode = node;
				roads[roadIndex].travelMinutes = curr->travelMinutes;
				roads[roadIndex].closedFrom = curr->closedFrom;
				roads[roadIndex].closedUntil = curr->closedUntil;
				roadIndex ++;
			}
			curr = curr->next;
		}
	}
	return roadIndex;
}

/* Free a given row of an adjacency list */
void freeList(RoadMap r, struct adjNode *l) {
	struct adjNode *curr = l;
	while (curr != NULL) {
		struct adjNode *temp = curr->next;
		free(curr);
		curr = temp;
		r->numRoads --;
	}
}

/* Check the number of roads that are currently connected to the vertices */
bool checkMaxRoad(RoadMap map, Vertex node1, Vertex node2) {
	struct adjNode *curr = map->edges[node1];
	int maxNode1 = 0;
	while (curr != NULL) {
		maxNode1 ++;
		curr = curr->next;
	}

	curr = map->edges[node2];
	int maxNode2 = 0;
	while (curr != NULL) {
		maxNode2 ++;
		curr = curr->next;
	}

	if ((maxNode1 < MAX_ROADS_PER_NODE) && (maxNode2 < MAX_ROADS_PER_NODE)) {
		return false;
	}
	return true;
}

/* Check if there is already a road connected between 2 nodes */
bool checkAlreadyRoad(RoadMap map, Vertex node1, Vertex node2) {
	struct adjNode *curr = map->edges[node1];
	while (curr != NULL) {
		if (curr->v == node2) {
			return true;
		}
		curr = curr->next;
	}
	curr = map->edges[node2];
	while (curr != NULL) {
		if (curr->v == node1) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

/* Only inserts a one way road (singe edge) between 2 nodes */
void roadInsertOneWay(RoadMap map, int node1, int node2, int travelMinutes) {
	map->edges[node1] = listInsert(map->edges[node1], node2, travelMinutes);
}

/* Insert into a adjacency list */
struct adjNode *listInsert(struct adjNode *head, int node2, int travelMinutes) {
	struct time fakeTime;
	fakeTime.hour = 12;
	fakeTime.minute = 12;

	if (head == NULL) {
		struct adjNode *new = malloc(sizeof(struct adjNode));
		new->v = node2;
		new->travelMinutes = travelMinutes;
		new->next = NULL;
		new->closedFrom = fakeTime;
		new->closedUntil = fakeTime;
		return new;
	}
	if (node2 < head->v) {
		struct adjNode *new = malloc(sizeof(struct adjNode));
		new->v = node2;
		new->travelMinutes = travelMinutes;
		new->closedFrom = fakeTime;
		new->closedUntil = fakeTime;
		new->next = head;
		return new;
	}
	head->next = listInsert(head->next, node2, travelMinutes);
	return head;
}
////////////////////////////////////////////////////////////////////////
// Task 2
/* Pre-process info about a roadMap such as islands and paths */
void RoadMapProcessIslands(RoadMap map) {
	for (Vertex v = 0; v < map->numNodes; v ++) {
		struct adjNode *curr = map->edges[v];
		while (curr != NULL) {
			Vertex w = curr->v;
			map->tc[v][w] = true;
			curr = curr->next;
		}
	}

	for (Vertex v = 0; v < map->numNodes; v ++) {
		for (Vertex w = 0; w < map->numNodes; w ++) {
			for (Vertex x = 0; x < map->numNodes; x ++) {
				if (map->tc[w][v] && map->tc[v][x]) {
					map->tc[w][x] = true;
				}
			}
		}
	}

	int islandNo = 0;
	for (Vertex v = 0; v < map->numNodes; v ++) {
		bool op = false;
		for (Vertex w = 0; w < map->numNodes; w ++) {
			if (v == w && map->islands[v] == -1) {
				map->islands[v] = islandNo;
				op = true;
			}
			if (checkAlreadyRoad(map, v, w) || map->tc[v][w] == true) {
				if (map->islands[w] == -1) {
					map->islands[w] = islandNo;
					op = true;
				}
			}
		}
		if (op == true) {
			islandNo ++;
		}
	}
	for (int i = 0; i < islandNo; i ++) {
		map->islandsInfo[i].islandNo = i;
	}
	map->numIslands = islandNo;
}	

/* Return number of how many different islands are in a map */
int RoadMapNumIslands(RoadMap map) {
	return map->numIslands;
}

/* Return if two nodes are on same island */
bool RoadMapOnSameIsland(RoadMap map, int node1, int node2) {
	return map->islands[node1] == map->islands[node2];
}

/* Set the island name that a particular node is on */
void RoadMapSetIslandName(RoadMap map, int node, char *name) {
	strcpy(map->islandsInfo[map->islands[node]].islandName, name);
}

/* Get the island name that a particular node is on */
char *RoadMapGetIslandName(RoadMap map, int node) {
	return map->islandsInfo[map->islands[node]].islandName;
}

////////////////////////////////////////////////////////////////////////
// Task 3
/* Add a traffic light at a node */
void RoadMapAddTrafficLights(RoadMap map, int node) {
	map->nodeTrafficLights[node] = true;
}

/* Return if a node has traffic lights */
bool RoadMapHasTrafficLights(RoadMap map, int node) {
	return map->nodeTrafficLights[node];
}

////////////////////////////////////////////////////////////////////////
// Task 4

/* Set close time of a given road, which closes the road during a certain period of time */
void RoadMapSetClosedTimes(RoadMap map, int node1, int node2,
                           struct time from, struct time until) {
	struct adjNode *curr = map->edges[node1];
	while (curr != NULL) {
		Vertex w = curr->v;
		if (w == node2) {
			curr->closedFrom = from;
			curr->closedUntil = until;
			return;
		}
		curr = curr->next;
	}
}


