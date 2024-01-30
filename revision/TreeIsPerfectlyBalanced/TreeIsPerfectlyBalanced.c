
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
int findHeight(Tree t);
int findNodes(Tree t);

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) {
		return true;
	}

	bool res = TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right);
	int left = findNodes(t->left);
	int right = findNodes(t->right);
	if (abs(left - right) > 1) {
		return false;
	}
	return res;
}

int findNodes(Tree t) {
	if (t == NULL) {
		return 0;
	}
	return 1 + findNodes(t->left) + findNodes(t->right);
}