#include <stdio.h>
#include <stdlib.h>
#include "Sets.h"

#define MAX 8

struct set {
    Item* elems;
    Item size;
    Item Capacity;
};

void ShiftUp(Set s, int mid, int value);


Set SetNew(void) {
    Set new = malloc(sizeof(struct set));
    new->elems = malloc(sizeof(int) * MAX);
    new->size = 0;
    new->Capacity = 8;
    return new;
}

void SetInsert(Set s, Item value) {
    if (s->size == 0) {
        (s->elems)[s->size] = value;
        s->size ++;
        return;
    }
    int lo = 0;
    int hi = s->size - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if ((s->elems)[mid] >= value) {
            if ((s->size) == (s->Capacity)) {
                return;
            }
            if ((s->elems)[mid] == value) {
                printf("Item in sets!\n");
                return;
            }
            s->size ++;
            ShiftUp(s, mid, value);
            return;
        } else {
            lo = mid + 1;
        }
    }

    (s->elems)[s->size] = value;
    s->size ++;
    return;
}

void SetShow(Set s) {
    printf("entering set show!\n");
    for (int i = 0; i < s->size; i ++) {
        printf("%d\n", (s->elems)[i]);
    }
    printf("exiting set show!\n");
}

void ShiftUp(Set s, int mid, int value) {
    int temp;
    int next;
    for (int i = mid; i < s->size; i ++) {
        temp = (s->elems)[i];
        next = (s->elems)[i + 1];
        if (i == mid) {
            temp = (s->elems)[i];
            (s->elems)[i] = value;
            next = (s->elems)[i + 1];
        } else {
            (s->elems)[i] = temp;
            temp = next;
            if (i < (s->size - 1)) {
                next = (s->elems)[i + 1];
            }
        }
    }
}