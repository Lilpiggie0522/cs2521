#include <stdlib.h>

int bstCountOdds(struct node *t) {
    if (t == NULL) {
        return 0;
    }

    if (t->value % 2 == 1) {
        return bstCountOdds(t->left) + bstCountOdds(t->right) + 1;
    }
    return bstCountOdds(t->left) + bstCountOdds(t->right);
}