// Implementation of the FriendBook ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "List.h"
#include "Map.h"
#include "Queue.h"

#define DEFAULT_CAPACITY 1 // DO NOT change this line

struct adjNode {
    int v;
    struct adjNode *next;
};



// DO NOT modify this struct
struct fb {
    int numPeople;
    int capacity;

    char **names; // the id of a person is simply the index
                  // that contains their name in this array
    
    Map nameToId; // maps names to ids

    struct adjNode **adj; // adjacency lists, kept in increasing order
};

static void increaseCapacity(Fb fb);
static char *myStrdup(char *s);
static int nameToId(Fb fb, char *name);

static struct adjNode *adjListInsert(struct adjNode *l, int v);
static struct adjNode *newAdjNode(int v);
static bool inAdjList(struct adjNode *l, int v);
static void freeAdjList(struct adjNode *l);
void freeGuy2(Fb fb, int guyId1, int guyId2);
void lookSuspeciousIdGuy2(Fb fb, int guy2Id, int suspeciousId, List l);
bool checkIsFriend(int arr[], int size, int row_num);
void bubbleSort(struct recommendation recs[], int lo, int hi);
void swap(struct recommendation recs[], int i, int j);
////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb FbNew(void) {
    Fb fb = malloc(sizeof(*fb));
    if (fb == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    fb->numPeople = 0;
    fb->capacity = DEFAULT_CAPACITY;
    
    fb->names = calloc(fb->capacity, sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    fb->nameToId = MapNew();

    fb->adj = calloc(fb->capacity, sizeof(struct adjNode *));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return fb;
}

void FbFree(Fb fb) {
    for (int i = 0; i < fb->capacity; i++) {
        freeAdjList(fb->adj[i]);
    }
    free(fb->adj);

    MapFree(fb->nameToId);

    for (int i = 0; i < fb->numPeople; i++) {
        free(fb->names[i]);
    }
    free(fb->names);
    
    free(fb);
}

int FbNumPeople(Fb fb) {
    return fb->numPeople;
}

bool FbAddPerson(Fb fb, char *name) {
    if (fb->numPeople == fb->capacity) {
        increaseCapacity(fb);
    }

    if (!MapContains(fb->nameToId, name)) {
        int id = fb->numPeople++;
        fb->names[id] = myStrdup(name);
        MapSet(fb->nameToId, name, id);
        return true;
    } else {
        return false;
    }
}

static void increaseCapacity(Fb fb) {
    int newCapacity = fb->capacity * 2;
    
    fb->names = realloc(fb->names, newCapacity * sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->names[i] = NULL;
    }
    
    fb->adj = realloc(fb->adj, newCapacity * sizeof(struct adjNode));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->adj[i] = NULL;
    }
    
    fb->capacity = newCapacity;
}

bool FbHasPerson(Fb fb, char *name) {
    return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
    List l = ListNew();
    for (int id = 0; id < fb->numPeople; id++) {
        ListAppend(l, fb->names[id]);
    }
    return l;
}

bool FbFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    assert(id1 != id2);

    if (!inAdjList(fb->adj[id1], id2)) {
        fb->adj[id1] = adjListInsert(fb->adj[id1], id2);
        fb->adj[id2] = adjListInsert(fb->adj[id2], id1);
        return true;
    } else {
        return false;
    }
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    return inAdjList(fb->adj[id1], id2);
}

////////////////////////////////////////////////////////////////////////
// Your tasks

int FbNumFriends(Fb fb, char *name) {
    // TODO: Complete this function
    int guyId = -1;
    for (int i = 0; i < fb->numPeople; i ++) {
        if (strcmp(name, fb->names[i]) == 0) {
            guyId = i;
            break;
        }
    }
    // v
    if (guyId == -1) {
        return 0;
    }
    int numFriends = 0;
    struct adjNode *guysFriend = (fb->adj)[guyId];
    while (guysFriend != NULL) {
        numFriends ++;
        guysFriend = guysFriend->next;
    }
    return numFriends;
}

bool FbUnfriend(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    int guyId1 = -1;
    int guyId2 = -1;
    for (int i = 0; i < fb->numPeople; i ++) {
        if (strcmp(name1, fb->names[i]) == 0) {
            guyId1 = i;
        }
        if (strcmp(name2, fb->names[i]) == 0) {
            guyId2 = i;
        }
    }
    // v
    if (guyId1 == -1 || guyId2 == -1) {
        return false;
    }
    struct adjNode *guy1List = fb->adj[guyId1];
    if (guy1List == NULL) { // guy has no friend
        return false;
    }
    struct adjNode *last = NULL;
    while (guy1List != NULL) {
        if (guy1List->v == guyId2) {
            if (last != NULL) {
                last->next = guy1List->next;
                
            } else {
                struct adjNode *new = guy1List->next;
                
                fb->adj[guyId1] = new;
                
            }
            free(guy1List);
            freeGuy2(fb, guyId1, guyId2);
            return true;
        } 
        last = guy1List;
        guy1List = guy1List->next;
    }
    return false;
}

void freeGuy2(Fb fb, int guyId1, int guyId2) {
    struct adjNode *last = NULL;
    struct adjNode *guy2List = fb->adj[guyId2];
    while (guy2List != NULL) {
        if (guy2List->v == guyId1) {
            if (last != NULL) {
                last->next = guy2List->next;
            } else {
                struct adjNode *new = guy2List->next;
                
                fb->adj[guyId2] = new;
            }
            free(guy2List);
            return;
        } 
        last = guy2List;
        guy2List = guy2List->next;
    }
}

List FbMutualFriends(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    List l = ListNew();
    int guyId1 = -1;
    int guyId2 = -1;
    int i;
    for (i = 0; i < fb->numPeople; i ++) {
        if (strcmp(fb->names[i], name1) == 0) {
            guyId1 = i;
        }    
        if (strcmp(fb->names[i], name2) == 0) {
            guyId2 = i;
        }
    }
    // v
    if (guyId1 == -1 || guyId2 == -1) {
        return l;
    }
    struct adjNode *guy1List = fb->adj[guyId1];
    while (guy1List != NULL) {
        int suspeciousId = guy1List->v;
        lookSuspeciousIdGuy2(fb, guyId2, suspeciousId, l);
        guy1List = guy1List->next;
    }
    return l;
}

void lookSuspeciousIdGuy2(Fb fb, int guyId2, int suspeciousId, List l) {
    struct adjNode *guy2List = fb->adj[guyId2];
    while (guy2List != NULL) {
        if (guy2List->v == suspeciousId) {
            ListAppend(l, fb->names[suspeciousId]);
            return;
        }
        guy2List = guy2List->next;
    }
}

int FbFriendRecs1(Fb fb, char *name, struct recommendation recs[]) {
    // TODO: Complete this function
    
    int guyId = -1;
    int name_index;
    for (name_index = 0; name_index < fb->numPeople; name_index ++) {
        if (strcmp(fb->names[name_index], name) == 0) {
            guyId = name_index;
            break;
        }
    }
    //  v
    // guy does not exist
    if (guyId == -1) {
        return 0;
    }

    struct adjNode *guyFriends = fb->adj[guyId];
    // guy has no friends
    if (guyFriends == NULL) {
        return 0;
    }
    int numFriends = FbNumFriends(fb, name);
    //  v
    int *isFriends = malloc(sizeof(int) * numFriends);
    for (int i = 0; i < numFriends; i ++) {
        isFriends[i] = -1;
    }
    int friendArrCounter = 0;
    // compile an array of friends using id as elements that should not be visted again
    while (guyFriends != NULL) {
        isFriends[friendArrCounter] = guyFriends->v;
        friendArrCounter ++;
        guyFriends = guyFriends->next;
    }
    int recs_counter = 0; // rec struct array counter

    for (int row = 0; row < fb->numPeople; row ++) {    //  v
        if (!checkIsFriend(isFriends, numFriends, row) && row != guyId) { // v^2
            List l = FbMutualFriends(fb, name, fb->names[row]);//   O(V*(V + V^2))  --> O(V^2 + V^3) = O(V^3)
            int numMutual = ListSize(l);
            if (numMutual != 0) {
                recs[recs_counter].name = (fb->names)[row];
                // recs[recs_counter].name = malloc(sizeof(char) * (strlen(fb->names[row]) + 1));
                // strcpy(recs[recs_counter].name, fb->names[row]);
                // printf("recommend name is %s\n", fb->names[row]);
            
                recs[recs_counter].numMutualFriends = numMutual;
                // printf("recommend num is %d\n", numMutual);
                recs_counter ++;
            }
            
            ListFree(l);
        }
    }
    free(isFriends);
    int numofRecommend = recs_counter;
    bubbleSort(recs, 0, numofRecommend - 1);
    // printf("num of recommend is %d\n", numofRecommend);
    return numofRecommend;
}

bool checkIsFriend(int arr[], int size, int row_num) {
    for (int i = 0; i < size; i ++) {
        if (arr[i] == row_num) {
            return true;
        }
    }
    return false;
}

void bubbleSort(struct recommendation recs[], int lo, int hi) {
    for (int i = lo; i < hi; i ++) {
        bool swapped = false;
        for (int j = hi; j > i; j --) {
            if (recs[j - 1].numMutualFriends < recs[j].numMutualFriends) {
                swap(recs, j - 1, j);
            }
        }
        if (swapped == false) {
            return;
        }
    }
}

void swap(struct recommendation recs[], int i, int j) {
    struct recommendation temp = recs[j];
    recs[j] = recs[i];
    recs[i] = temp;
}



// outer loop 


////////////////////////////////////////////////////////////////////////
// Optional task

List FbFriendRecs2(Fb fb, char *name) {
    // TODO: Complete this function
    List l = ListNew();
   
    return l;
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Converts a name to an ID. Raises an error if the name doesn't exist.
static int nameToId(Fb fb, char *name) {
    if (!MapContains(fb->nameToId, name)) {
        fprintf(stderr, "error: person '%s' does not exist!\n", name);
        exit(EXIT_FAILURE);
    }
    return MapGet(fb->nameToId, name);
}

static struct adjNode *adjListInsert(struct adjNode *l, int v) {
    if (l == NULL || v < l->v) {
        struct adjNode *new = newAdjNode(v);
        new->next = l;
        return new;
    } else if (v == l->v) {
        return l;
    } else {
        l->next = adjListInsert(l->next, v);
        return l;
    }
}

static struct adjNode *newAdjNode(int v) {
    struct adjNode *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->v = v;
    n->next = NULL;
    return n;
}

static bool inAdjList(struct adjNode *l, int v) {
    for (struct adjNode *n = l; n != NULL && n->v <= v; n = n->next) {
        if (n->v == v) {
            return true;
        }
    }
    return false;
}

static void freeAdjList(struct adjNode *l) {
    struct adjNode *n = l;
    while (n != NULL) {
        struct adjNode *temp = n;
        n = n->next;
        free(temp);
    }
}

