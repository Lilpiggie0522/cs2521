
#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"
int getSize(BSTree t);
void BSTTraverse(BSTree t, int *arr, int *index);

int BSTreeGetKth(BSTree t, int k) {
	// printf("size of tree is %d\n", getSize(t));
	int size = getSize(t);
	int *arr = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i ++) {
		arr[i] = -1;
	}
	int index = 0;
	BSTTraverse(t, arr, &index);
	if (arr[k] != -1) {
		int num = arr[k];
		free(arr);
		return num;
	}
	free(arr);
	return -1;
}

int getSize(BSTree t) {
	if (t == NULL) {
		return 0;
	}
	return getSize(t->left) + getSize(t->right) + 1;
}

void BSTTraverse(BSTree t, int *arr, int *index) {
	if (t == NULL) {
		return;
	}
	BSTTraverse(t->left, arr, index);
	arr[*index] = t->value;
	(*index) ++;
	BSTTraverse(t->right, arr, index);
}