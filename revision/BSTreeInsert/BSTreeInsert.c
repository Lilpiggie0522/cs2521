
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	if (t == NULL) {
		struct BSTNode *new = malloc(sizeof(struct BSTNode));
		new->value = val;
		new->left = NULL;
		new->right = NULL;
		return new;
	}

	if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);
	} else if (val > t->value) {
		t->right = BSTreeInsert(t->right, val);
	} else {
		return t;
	}
	return t;
}

