#include <stdlib.h>


int bstNodeLevel(struct node *t, int key) {
    if (t == NULL) {
        return -1;
    }
    if (t->value == key) {
        return 0;
    }
    if (key < t->value) {
        int level = bstNodeLevel(t->left, key);
        if (level == -1) {
            return -1;
        }
        return 1 + level;
    }
    if (key > t->value) {
        int level = bstNodeLevel(t->right, key);
        if (level == -1) {
            return -1;
        }
        return 1 + level;
    }
}
