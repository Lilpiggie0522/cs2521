
#include <stdlib.h>

#include "tree.h"
void doSum(Tree t, int *sum);

int TreeSumOdds(Tree t) {
	if (t == NULL) {
		return 0;
	}
	int sum = 0;
	doSum(t, &sum);
	return sum;
}

void doSum(Tree t, int *sum) {
	if (t == NULL) {
		return;
	}
	doSum(t->left, sum);
	doSum(t->right, sum);
	if (t->value % 2 != 0) {
		(*sum) += t->value;
	}
}

