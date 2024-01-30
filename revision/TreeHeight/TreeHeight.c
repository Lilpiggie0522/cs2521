
#include <stdlib.h>

#include "tree.h"
int findTreeHeight(Tree t);

int max(int value1, int value2);

int TreeHeight(Tree t) {
    return findTreeHeight(t);
}

int findTreeHeight(Tree t) {
    if (t == NULL) {
        return -1;
    }
    if (t->left == NULL && t->right == NULL) {
        return 0;
    }

    int left = findTreeHeight(t->left);
    int right = findTreeHeight(t->right);
    int height = max(left, right) + 1;
    return height;
}

int max(int value1, int value2) {
    if (value2 > value1) {
        return value2;
    }
    return value1;
}