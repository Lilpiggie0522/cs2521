#include <stdlib.h>


int bstCountInternal(struct node *t) {
    if (t == NULL) {
        return 0;
    }
    if (t->left != NULL || t->right != NULL) {
        return 1 + bstCountInternal(t->left) + bstCountInternal(t->right);
    }
    return bstCountInternal(t->left) + bstCountInternal(t->right);
}