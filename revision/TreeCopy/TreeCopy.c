
#include "tree.h"
Tree doCopy(Tree t, int depth, int lvl, Tree new);
Tree insertion(Tree t, int value);

Tree TreeCopy(Tree t, int depth) {
	if (t == NULL || depth == -1) {
		return NULL;
	}
	
	Tree new = NULL;
	new = doCopy(t, depth, 0, new);
	return new;
}

Tree doCopy(Tree t, int depth, int lvl, Tree new) {
	if (t == NULL) {
		return NULL;
	}
	if (lvl <= depth) {
		new = insertion(new, t->value);
		// printf("inserting %d\n", t->value);
		// printTree(new);
	}
	doCopy(t->left, depth, lvl + 1, new);
	doCopy(t->right, depth, lvl + 1, new);
	return new;
}

Tree insertion(Tree t, int value) {
	if (t == NULL) {
		Tree new = malloc(sizeof(struct node));
		new->left = NULL;
		new->right = NULL;
		new->value = value;
		return new;
	}

	if (value < t->value) {
		t->left = insertion(t->left, value);
	} else if (value > t->value) {
		t->right = insertion(t->right, value);
	} else {
		return t;
	}
	return t;
}