
#include <stdlib.h>

#include "BSTree.h"
int DoBSTreeNodeDepth(BSTree t, int key, int level);

int BSTreeNodeDepth(BSTree t, int key) {
	if (t == NULL) {
		return -1;
	}
	return DoBSTreeNodeDepth(t, key, 0);
}

int DoBSTreeNodeDepth(BSTree t, int key, int level) {
	if (t == NULL) {
		return -1;
	}
	if (key < t->value) {
		return DoBSTreeNodeDepth(t->left, key, level + 1);
	} else if (key > t->value) {
		return DoBSTreeNodeDepth(t->right, key, level + 1);
	} else {
		return level;
	}
}
