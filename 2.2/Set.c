#include <stdio.h>
#include <stdlib.h>
#include "Set.h"
#define MAX_NUM 99

struct SetRep {
    int size;
    int elements[MAX_NUM];
};

Set SetCreate() {
    Set NewSet;
    // struct SetRep* NewSet;
    if ((NewSet = malloc(sizeof(struct SetRep))) == NULL) {
        fprintf(stderr, "Insufficient Memory for Set\n");
        exit(EXIT_FAILURE);
    }
    NewSet->size = 0;
    return NewSet;
}

void SetInsert(Set s, int n) {
    for (int i = 0; i < s->size; i ++) {
        if ((s->elements)[i] == n) {
            printf("Duplicate found!\n");
            return;    
        }
    }
    if ((s->size) < MAX_NUM) {
        (s->elements)[s->size] = n;
        (s->size) ++;
    } else {
        printf("MAX num reached!\n");
    }
}

void SetShow(Set s) {
    printf("{");
    for (int i = 0; i < s->size; i ++) {
        printf("%d", (s->elements)[i]);
        if (i < s->size - 1) {
            printf(",");
        }
    }
    printf("}");
}