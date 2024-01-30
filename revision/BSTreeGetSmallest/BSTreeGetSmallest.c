
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	if (t == NULL) {
		return NULL;
	}
	if (t->left == NULL) {
		return t;
	}

	BSTree min = t;
	if (t->left == NULL && t->right == NULL) {
		return min;
	}

	return BSTreeGetSmallest(t->left);
}

