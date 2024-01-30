#include <stdio.h>


bool hasTwoSum(int arr[], int value, int size) {
    Tree t = newTree();
    for (int i = 0; i < size; i ++) {
        if (inThere(t, value - arr[i])) {
            return true;
        }
    }
    return false;
}

bool inThere(struct tree *t, int value) {
    if (t == NULL) {
        return false;
    }
    if (value < t->value) {
        return inThere(t->left, value);
    } else if (value > t->value) {
        return inThere(t->right, value);
    } else {
        return true;
    }
}