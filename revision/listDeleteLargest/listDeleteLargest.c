
#include "list.h"

int listDeleteLargest(List l) {
	Node prev = NULL;
	Node temp = NULL;
	Node next = NULL;
	Node big = NULL;

	Node curr = l->head;
	if (curr == NULL) {
		return 0;
	}
	if (curr->next == NULL) {
		l->head = NULL;
		return curr->value;
	}

	
	big = curr;
	prev = curr;
	while (curr != NULL) {
		if (big != NULL && curr->value > big->value) {
			prev = temp;
			big = curr;
		}
		temp = curr;	
		curr = curr->next;
	}
	next = big->next;
	// printf("next value is %d\n", next->value);
	prev->next = next;
	// printf("prev value is %d\n", prev->value);
	int num = big->value;
	free(big);
	return num;
}

