
#include "list.h"

bool listIsOrdered(List l) {
	if (l->head == NULL) {
		return true;
	}
	if (l->head->next == NULL) {
		return true;
	}

	Node curr = l->head;
	bool first = true;
	bool small = false;
	bool big = false;
	while (curr != NULL) {
		while (curr->next != NULL) {
			if (first == true) {
				if (curr->next->value > curr->value) {
					big = true;
					first = false;
				} else if (curr->next->value < curr->value) {
					small = true;
					first = false;
				}
			} else {
				if (curr->next->value > curr->value) {
					big = true;
				} else if (curr->next->value < curr->value) {
					small = true;
				}
			}
			if (big == true && small == true) {
				return false;
			}
			curr = curr->next;
		}
		curr = curr->next;
	}
	return true;
}

