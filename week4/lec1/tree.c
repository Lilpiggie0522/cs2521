#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

#define PERIODIC_INDEX 3

struct node {
    int value;
    int height;
    Tree left;
    Tree right;
};

int main(int argc, char *argv[]) {
    Tree t = createNew(6);
    t = avlInsertHeight(t, 2);
    t = avlInsertHeight(t, 9);
    t = avlInsertHeight(t, 1);
    t = avlInsertHeight(t, 5);
    t = avlInsertHeight(t, 8);
    t = avlInsertHeight(t, 3);
    t = avlInsertHeight(t, 4);

    // t = avlInsert(t, 2);
    // t = avlInsert(t, 9);
    // t = avlInsert(t, 1);
    // t = avlInsert(t, 5);
    // t = avlInsert(t, 8);
    // t = avlInsert(t, 3);
    // t = avlInsert(t, 4);
    
    // t = avlInsert(t, 5);
    // t = avlInsert(t, 4);
    // t = avlInsert(t, 3);
    // t = avlInsert(t, 2);
    // t = avlInsert(t, 1);

    // t = avlInsertHeight(t, 5);
    // t = avlInsertHeight(t, 4);
    // t = avlInsertHeight(t, 3);
    // t = avlInsertHeight(t, 2);
    // t = avlInsertHeight(t, 1);

    printTree(t);
    printf("\n");
    
    int height = t->height;
    printf("height is %d\n", height);
    return 0;
}

Tree createNew(int value) {
    Tree new = malloc(sizeof(struct node));
    new->value = value;
    new->height = 0;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Tree bstNew(void) {
	return NULL;
}

Tree bstInsert(Tree t, int value) {
    if (t == NULL) {
        return createNew(value);
    }
    if (value < t->value) {
        t->left = bstInsert(t->left, value);
    } else if (value > t->value) {
        t->right = bstInsert(t->right, value);
    } else {
        return t;
    }
    return t;
}

int bstSize(Tree t) {
    if (t == NULL) {
        return 0;
    }

    return 1 + bstSize(t->left) + bstSize(t->right);
}

Tree rotateRight(Tree t) {
    if (t == NULL || t->left == NULL) return t;
    struct node *new_node = t->left;
    t->left = new_node->right;
    new_node->right = t;
    return new_node;
}

Tree rotateLeft(Tree t) {
    if (t == NULL || t->right == NULL) return t;
    struct node *new_node = t->right;
    t->right = new_node->left;
    new_node->left = t;
    return new_node;
}

void printTree(Tree t) {
    if (t == NULL) {
        return;
    }
    printf("%d\n", t->value);
    printTree(t->left);
    printTree(t->right);
}

Tree partition(Tree t, int i) {
    int m = bstSize(t->left);
    if (i < m) {
        t->left = partition(t->left, i);
        t = rotateRight(t);
    } else if (i > m) {
        t->right = partition(t->right, i - m - 1);
        t = rotateLeft(t);
    }
    return t;
}

Tree rebalance(Tree t) {
    int size = bstSize(t);
    if (size < 3) {
        return t;
    }
    t = partition(t, size / 2);
    t->left = rebalance(t->left);
    t->right = rebalance(t->right);
    return t;
}

Tree periodicRebalancingInsert(Tree t, int value) {
    t = bstInsert(t, value);
    int size = bstSize(t);
    if (size % PERIODIC_INDEX == 0) {
        t = rebalance(t);
    }
    return t;
}

Tree insertAtRoot(Tree t, int value) {
    if (t == NULL) {
        t = createNew(value);
        return t;
    }
    if (value < t->value) {
        t->left = insertAtRoot(t->left, value);
        t = rotateRight(t);
    } else if (value > t->value) {
        t->right = insertAtRoot(t->right, value);
        t = rotateLeft(t);
    }
    return t;
}

Tree avlInsert(Tree t, int value) {
    if (t == NULL) {
        t = createNew(value);
        return t;
    }

    if (value < t->value) {
        t->left = avlInsert(t->left, value);
    } else if (value > t->value) {
        t->right = avlInsert(t->right, value);
    } else {
        return t;
    }
    int left_height = avlHeight(t->left);
    int right_height = avlHeight(t->right);
    if (left_height - right_height > 1) {
        if (value > t->left->value) {
            t->left = rotateLeft(t->left) ;
        }
        t = rotateRight(t);
    } else if (right_height - left_height > 1) {
        if (value < t->right->value) {
            t->right = rotateRight(t->right);
        }
        t = rotateLeft(t);
    }
    return t;
}

int avlHeight(Tree t) {
    if (t == NULL) {
        return -1;
    }
    int left_height = avlHeight(t->left);
    int right_height = avlHeight(t->right);
    if (left_height > right_height) {
        return 1 + left_height;
    } else {
        return 1 + right_height;
    }
}

Tree avlInsertHeight(Tree t, int value) {
    // printf("function executing!\n");
    if (t == NULL) {
        return createNew(value);
    }
    if (value < t->value) {
        t->left = avlInsertHeight(t->left, value);
    } else if (value > t->value) {
        t->right = avlInsertHeight(t->right, value);
    } else {
        return t;
    }
    int left_height;
    int right_height;
    if (t->left == NULL) {
        left_height = -1;
        if (t->right == NULL) {
            right_height = -1;
        } else {
            right_height = t->right->height;
        }
    } else if (t->right == NULL) {
        left_height = t->left->height;
        right_height = -1;
    } else {
        left_height = t->left->height;
        right_height = t->right->height;
    }
    if (left_height - right_height > 1) {
        if (value > t->left->value) {
            t->left = rotateLeft(t->left);
            t->left->left->height = 1 + max(t->left->left->left, t->left->left->right);
            t->left->height = 1 + max(t->left->left, t->left->right);
        }
        t = rotateRight(t);
        t->right->height = 1 + max(t->right->left, t->right->right);
        t->height = 1 + max(t->left, t->right);
    } else if (right_height - left_height > 1) {
        if (value < t->right->value) {
            t->right = rotateRight(t->right);
            t->right->right->height = 1 + max(t->right->right->left, t->right->right->right);
            t->right->height = 1 + max(t->right->left, t->right->right);
        }
        t = rotateLeft(t);
        t->left->height = 1 + max(t->left->left, t->left->right);
        t->height = 1 + max(t->left, t->right);
    }
    t->height = 1 + max(t->left, t->right);
    // printf("height is %d\n", t->height);
    return t;
}

int max(struct node *left, struct node *right) {
    int left_h;
    int right_h;
    if (left == NULL) {
        left_h = -1;
    }
    if (right == NULL) {
        right_h = -1;
    }
    if (left != NULL) {
        left_h = left->height;
    }
    if (right != NULL) {
        right_h = right->height;
    }

    if (left_h > right_h) {
        return left_h;
    }
    return right_h;
}