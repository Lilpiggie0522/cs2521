
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "navigator.h"
#include "RoadMap.h"
#include "time.h"
int *dijkstraSSSP(RoadMap map, int src, int dest, int *arrSize);
bool vSetEmpty(int *vSet, int size);
int findMinimal(int *dist, int size, int *vSet);
void relaxAlong(int v, int w, int weight, int *dist, int *pred);
bool vSetRemoved(int *vSet, int node);
int getTravelMinutes(int node1, int node2, RoadMap map);
struct time getClosedTime(RoadMap map, int node1, int node2);
struct time getClosedUntil(RoadMap map, int node1, int node2);
int *improvisedDijkstraSSSP(RoadMap map, int src, int dest, struct time departure, struct time *finalMoment);
void improvisedRelax(int v, int w, struct time *arrival, int *pred, struct time finishTime);
int findEarliestTime(struct time *arrival, int size, int *vSet);
int getTotalDuration(int src, int dest, int *pred, RoadMap map);
int *getRouteArray(int src, int dest, int *pred, int *returnSize);
////////////////////////////////////////////////////////////////////////
// Task 3

struct route navigate(RoadMap map, int fromNode, int toNode,
                      struct time time) {
	struct route route = {
		.fromNode = fromNode,
		.toNode = toNode,
		.start = time,
		.numLegs = 0,
		.legs = malloc(sizeof(struct leg) * (RoadMapNumNodes(map) - 1)),
		.totalDuration = 0
	};
	int arrSize = 0;
	int *arr = dijkstraSSSP(map, fromNode, toNode, &arrSize);
	if (arr == NULL) {
		free(route.legs);
		return route;
	}
	route.numLegs = arrSize - 1;
	bool lights = false;
	for (int i = 0; i < route.numLegs; i ++) {
		if (i == 0) {
			route.legs[i].fromNode = fromNode;
			route.legs[i].toNode = arr[i + 1];
			route.legs[i].start = time;
			int travelMinutes = getTravelMinutes(arr[i], arr[i + 1], map);
			if (travelMinutes == -1) {
				return route;
			}
			route.legs[i].duration = travelMinutes;
			route.totalDuration += travelMinutes;
			route.legs[i].end = timeAdd(time, travelMinutes);
		}
		//	Traffic light case light starts at 1
		if (i != 0) {
			if (RoadMapHasTrafficLights(map, arr[i])) {
				lights = true;
			}
			route.legs[i].fromNode = arr[i];
			route.legs[i].toNode = arr[i + 1];
			if (lights == true) {
				route.legs[i].start = timeAdd(route.legs[i - 1].end, TRAFFIC_LIGHT_WAIT);
				route.totalDuration += TRAFFIC_LIGHT_WAIT;
				lights = false;
			} else {
				route.legs[i].start = route.legs[i - 1].end;
			}
			int travelMinutes = getTravelMinutes(arr[i], arr[i + 1], map);
			if (travelMinutes == -1) {
				return route;
			}
			route.legs[i].duration = travelMinutes;
			route.totalDuration += travelMinutes;
			route.legs[i].end = timeAdd(route.legs[i].start, travelMinutes);
			route.end = route.legs[i].end;
		}
	}

	free(arr);
	return route;
}

/* Get how long it takes to trave from node1 to node2, not including traffic or sandStorm */
int getTravelMinutes(int node1, int node2, RoadMap map) {
	struct road *roads = malloc(sizeof(struct road) * MAX_ROADS_PER_NODE);
	if (roads == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	int num = RoadMapGetRoadsFrom(map, node1, roads);
	for (int i = 0; i < num; i ++) {
		if (roads[i].toNode == node2) {
			int travelMinutes = roads[i].travelMinutes;
			free(roads);
			return travelMinutes;
		}
	}
	free(roads);
	return -1;
}

/* A dijkstra function that returns an array which contains sssp from node1 to node2 */
int *dijkstraSSSP(RoadMap map, int src, int dest, int *arrSize) {
	int *dist = malloc(sizeof(int) * RoadMapNumNodes(map));
	if (dist == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	int *pred = malloc(sizeof(int) * RoadMapNumNodes(map));
	if (pred == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	//	mark it to -1 after visited, done in findMinimal helper function
	int *vSet = malloc(sizeof(int) * RoadMapNumNodes(map));
	if (vSet == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	for (int i = 0; i < RoadMapNumNodes(map); i ++) {
		dist[i] = INT_MAX;
		pred[i] = -1;
		vSet[i] = i;
	}
	dist[src] = 0;
	while (!vSetEmpty(vSet, RoadMapNumNodes(map))) {
		
		int v = findMinimal(dist, RoadMapNumNodes(map), vSet);
		struct road roads[MAX_ROADS_PER_NODE];
		int numNeibours = RoadMapGetRoadsFrom(map, v, roads);
		for (int j = 0; j < numNeibours; j ++) {
			int traffic = 0;
			if (RoadMapHasTrafficLights(map, roads[j].toNode)) {
				traffic = TRAFFIC_LIGHT_WAIT;
			}
			relaxAlong(v, roads[j].toNode, roads[j].travelMinutes + traffic, dist, pred);
		}
		
	}

	int *arr = getRouteArray(src, dest, pred, arrSize);
	free(dist);
	free(pred);
	free(vSet);
	return arr;
}

/* A function that loops through vSet to find if vSet is empty or not */
bool vSetEmpty(int *vSet, int size) {
	for (int i = 0; i < size; i ++) {
		if (vSet[i] != -1) {
			return false;
		}
	}
	return true;
}

/* A function that finds the node that contains the minimal distance */
int findMinimal(int *dist, int size, int *vSet) {
	int minimal = 0;
	for (int i = 0; i < size; i ++) {
		if (!vSetRemoved(vSet, i)) {
			minimal = i;
			break;
		}
	}
	for (int i = minimal; i < size; i ++) {
		if ((!vSetRemoved(vSet, i)) && (dist[i] < dist[minimal])) {
			minimal = i;
		}
	}
	vSet[minimal] = -1;
	return minimal;
}

/* A function that removes a node from vSet */
bool vSetRemoved(int *vSet, int node) {
	if (vSet[node] == -1) {
		return true;
	}
	return false;
}

/* A function that relaxes along an edge */
void relaxAlong(int v, int w, int weight, int *dist, int *pred) {
	if (dist[v] + weight < dist[w]) {
		dist[w] = dist[v] + weight;
		pred[w] = v;
	}
}
////////////////////////////////////////////////////////////////////////
// Task 4

struct route advancedNavigate(RoadMap map, int fromNode, int toNode,
                              struct time time) {					
	struct route route = {
		.fromNode = fromNode,
		.toNode = toNode,
		.numLegs = 0,
		.legs = malloc(sizeof(struct leg) * (RoadMapNumNodes(map) - 1)),
	};
	struct time finalMoment = {
		.hour = -1,
		.minute = -1
	};
	int *pred = improvisedDijkstraSSSP(map, fromNode, toNode, time, &finalMoment);
	route.end = finalMoment;
	
	/* since we dont have a way to record total duration when finding sssp,
	we have to traverse down the path found and keep track of total duration. */
	int totalDuration = getTotalDuration(fromNode, toNode, pred, map);
	route.totalDuration = totalDuration;

	/* Using arrival time - total duration to get start time, working backwards! */
	struct time startMoment = timeAdd(finalMoment, -(totalDuration));
	route.start = startMoment;

	int returnSize = 0;
	/* Return an array that is the shortest path from node1 to node2, 
	and capture its size in returnSize */
	int *arr = getRouteArray(fromNode, toNode, pred, &returnSize);
	if (arr == NULL) {
		free(route.legs);
		return route;
	}
	/* Adding all roads taken onto legs and update routes info in route struct */
	for (int i = 0; i < returnSize - 1; i ++) {
		if (i == 0) {
			route.legs[i].fromNode = fromNode;
			route.legs[i].toNode = arr[i + 1];
			route.legs[i].start = startMoment;
			int travelMinutes = getTravelMinutes(arr[i], arr[i + 1], map);
			if (travelMinutes == -1) {
				return route;
			}
			route.legs[i].end = timeAdd(startMoment, travelMinutes);
			route.legs[i].duration = travelMinutes;
		} else {
			route.legs[i].fromNode = arr[i];
			route.legs[i].toNode = arr[i + 1];
			route.legs[i].start = route.legs[i - 1].end;
			if (RoadMapHasTrafficLights(map, arr[i])) {
				route.legs[i].start = timeAdd(route.legs[i].start, TRAFFIC_LIGHT_WAIT);
			}
			int travelMinutes = getTravelMinutes(arr[i], arr[i + 1], map);
			if (travelMinutes == -1) {
				return route;
			}
			route.legs[i].end = timeAdd(route.legs[i].start, travelMinutes);
			route.legs[i].duration = travelMinutes;
		}
	}
	free(arr);
	free(pred);
	route.numLegs = returnSize - 1;
	return route;
}

/* Generate an array that contains sssp from node1 to node 2 */
int *getRouteArray(int src, int dest, int *pred, int *returnSize) {
	int w = dest;
	int size = 0;
	while (w != src) {
		size ++;
		w = pred[w];
		if (w == -1) {
			return NULL;
		}
	}
	size += 1;
	int *arr = malloc(sizeof(int) * size);
	if (arr == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	*returnSize = size;
	w = dest;
	int counter = size - 1;
	while (w != src) {
		arr[counter] = w;
		w = pred[w];
		counter --;
	}
	arr[0] = src;
	return arr;
}
/* get the total duration of a certain route, including traffic lights */
int getTotalDuration(int src, int dest, int *pred, RoadMap map) {
	int totalDuration = 0;
	int size = 0;
	int *arr = getRouteArray(src, dest, pred, &size);
	if (arr == NULL) {
		return 0;
	}
	for (int i = 0; i < size - 1; i ++) {
		if (i == 0) {
			int travelMinutes = getTravelMinutes(arr[i], arr[i + 1], map);
			totalDuration += travelMinutes;
		} else {
			if (RoadMapHasTrafficLights(map, arr[i])) {
				// printf("current node %d has lights\n", arr[i]);
				totalDuration += TRAFFIC_LIGHT_WAIT;
			}
			int travelMinutes = getTravelMinutes(arr[i], arr[i + 1], map);
			totalDuration += travelMinutes;
		}
	}
	free(arr);
	return totalDuration;
}

/* Returns a predecessor array that stores routes to sssp */
int *improvisedDijkstraSSSP(RoadMap map, int src, int dest, struct time departure, struct time *finalMoment) {
	int *pred = malloc(sizeof(int) * RoadMapNumNodes(map));
	if (pred == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	int *vSet = malloc(sizeof(int) * RoadMapNumNodes(map));
	if (vSet == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}

	struct time *arrival = malloc(sizeof(struct time) * RoadMapNumNodes(map));
	if (arrival == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	struct time infTime = {
			.hour = INT_MAX,
			.minute = INT_MAX
	};

	for (int i = 0; i < RoadMapNumNodes(map); i ++) {
		arrival[i] = infTime;
		pred[i] = -1;
		vSet[i] = i;
	}
	arrival[src] = departure;
	while (!vSetEmpty(vSet, RoadMapNumNodes(map))) {
		int v = findEarliestTime(arrival, RoadMapNumNodes(map), vSet);
		struct road roads[MAX_ROADS_PER_NODE];
		int numNeibours = RoadMapGetRoadsFrom(map, v, roads);
		for (int j = 0; j < numNeibours; j ++) {
			//	check traffic lights
			struct time currentTime = arrival[v];
			int traffic = 0;
			if (v != src) {
				if (RoadMapHasTrafficLights(map, v)) {
					traffic = TRAFFIC_LIGHT_WAIT;
				}
			}
			currentTime = timeAdd(currentTime, traffic);
			// check road closure
			// arrival time = current time + traffic + sandStorm

			// first check if there is sandStorm
			struct time closeFrom = getClosedTime(map, v, roads[j].toNode);
			struct time closeUntil = getClosedUntil(map, v, roads[j].toNode);
			int travelMinutes = getTravelMinutes(v, roads[j].toNode, map);
			struct time finishingTime = timeAdd(currentTime, travelMinutes);
			// there is sandStorm on these roads
			if (timeDiff(closeFrom, closeUntil) != 0) {
				// check timing
				// hours between road closed, definitely gonna wait
				if (finishingTime.hour > closeFrom.hour && finishingTime.hour < closeUntil.hour) {
					currentTime = timeAdd(closeUntil, travelMinutes);
				} else if (finishingTime.hour == closeFrom.hour) {
					// cant make it before road closure, and departured after road opens, so gonna wait
					if ((finishingTime.minute > closeFrom.minute) && (finishingTime.minute < (closeUntil.minute + travelMinutes))) {
						currentTime = timeAdd(closeUntil, travelMinutes);
					}
				} else if (finishingTime.hour == closeUntil.hour) {
					// leave before road re-opens so gonna wait
					if (finishingTime.minute < (closeUntil.minute + travelMinutes)) {
						currentTime = timeAdd(closeUntil, travelMinutes);
					}
				}
			} else {
				// no sandStorm at all, just go cuz traffic stop is already waited.
				currentTime = timeAdd(currentTime, travelMinutes);
			}
			//	check if current time to get to node w takes less time than what's stored in time relexation array
			improvisedRelax(v, roads[j].toNode, arrival, pred, currentTime);
		}
	}

	//	since we cannot return pred array and final arrival time at the same time,
	//	we use a pointer to capture the final arrival time for our time calculation later
	(*finalMoment).hour = arrival[dest].hour;
	(*finalMoment).minute = arrival[dest].minute;
	free(vSet);
	free(arrival);
	return pred;
}

/* A function that relexes along edges using time instead of distance/weight. */
void improvisedRelax(int v, int w, struct time *arrival, int *pred, struct time finishTime) {
	if (finishTime.hour <= arrival[w].hour) {
		if (finishTime.minute < arrival[w].minute) {
			arrival[w] = finishTime;
			pred[w] = v;
			return;
		}
	}
}

/* A function that find earliest time out of all times stored */
int findEarliestTime(struct time *arrival, int size, int *vSet) {
	int earliest = 0;
	for (int i = 0; i < size; i ++) {
		if (!vSetRemoved(vSet, i)) {
			earliest = i;
			break;
		}
	}
	
	for (int i = earliest; i < size; i ++) {
		if (!vSetRemoved(vSet, i)) {
			if (arrival[i].hour <= arrival[earliest].hour && arrival[i].minute < arrival[earliest].minute) {
				earliest = i;
			}
		}
	}
	vSet[earliest] = -1;
	return earliest;
}

/* Get time when road starts to close */
struct time getClosedTime(RoadMap map, int node1, int node2) {
	struct road *roads = malloc(sizeof(struct road) * MAX_ROADS_PER_NODE);
	if (roads == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	int num = RoadMapGetRoadsFrom(map, node1, roads);
	for (int i = 0; i < num; i ++) {
		if (roads[i].toNode == node2) {
			struct time closeTime = roads[i].closedFrom;
			free(roads);
			return closeTime;
		}
	}
	free(roads);
	struct time fakeTime = {
		.hour = -1,
		.minute = -1
	};
	printf("something wrong in getcloseTime\n");
	return fakeTime;
}

/* Get time when road re-opens */
struct time getClosedUntil(RoadMap map, int node1, int node2) {
	struct road *roads = malloc(sizeof(struct road) * MAX_ROADS_PER_NODE);
	if (roads == NULL) {
		fprintf(stderr, "not enough memory!\n");
	}
	int num = RoadMapGetRoadsFrom(map, node1, roads);
	for (int i = 0; i < num; i ++) {
		if (roads[i].toNode == node2) {
			struct time closeUntil = roads[i].closedUntil;
			free(roads);
			return closeUntil;
		}
	}
	free(roads);
	struct time fakeTime = {
		.hour = -1,
		.minute = -1
	};
	printf("something wrong in getclosedUntil\n");
	return fakeTime;
}

