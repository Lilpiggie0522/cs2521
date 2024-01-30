
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void doMinDiff(struct node *t, int l, int *prev, bool *firstVal, int *min);

int minDiff(struct node *t, int l) {
    int prev = -1;
    bool firstVal = true;
    int min = -1;
    doMinDiff(t, l, &prev, &firstVal, &min);
    return min;
}

void doMinDiff(struct node *t, int l, int *prev, bool *firstVal, int *min) {
    if (t == NULL) {
        return;
    }
    if (l == 0) {
        if ((*firstVal) == true) {
            *prev = t->key;
            *firstVal = false;
        } else {
            if (*min == -1) {
                *min = abs(t->key - *prev);
            } else if (t->key - *prev < *min) {
                *min = abs(t->key - *prev);
                
            }
            *prev = t->key;
        }
        return;
    } else {
        doMinDiff(t->left, l - 1, prev, firstVal, min);
        doMinDiff(t->right, l - 1, prev, firstVal, min);
    }
}



