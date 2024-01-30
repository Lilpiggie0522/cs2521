#include <stdio.h>


int bstCountGreater(struct node *t, int val) {
    if (t == NULL) {
        return 0;
    }
    if (t->value > val) {
        return 1 + bstCountGreater(t->left, val) + bstCountGreater(t->right, val);
    } else if (t->value <= val) {
        return bstCountGreater(t->right, val);
    }
}