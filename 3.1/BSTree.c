#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

struct Node {
    int num;
    Tree left, right;
} Node;

Tree TreeCreate(int n) {
    Tree s;
    if ((s = malloc(sizeof(struct Node))) != NULL) {
        s->num = n;
        s->left = NULL;
        s->right = NULL;
        return s;
    }
    fprintf(stderr, "No memory!\n");
    exit(EXIT_FAILURE);
}

Tree TreeInsert(Tree s, int n) {
    if (s == NULL) {
        return TreeCreate(n);
    } else if (n < (s->num)) {
        s->left = TreeInsert((s->left), n);
    } else if (n > (s->num)) {
        s->right = TreeInsert((s->right), n);
    }
    return s;
}

void TreeShow(Tree s) {
   
    if ((s->left) != NULL) {
        TreeShow(s->left);
    }

    if ((s->right) != NULL) {
        TreeShow(s->right);
    }
    
    printf("%d", s->num);
    return;
}