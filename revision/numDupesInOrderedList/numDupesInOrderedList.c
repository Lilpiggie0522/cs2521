
#include "list.h"
void listInsert(List l, Node n, int *num);

int numDupesInOrderedList(List l) {
	int count = 0;
	Node curr = l->head;
	while (curr != NULL && curr->next != NULL) {
		if (curr->value == curr->next->value) {
			count ++;
		}
		curr = curr->next;
	}
	return count;
}


