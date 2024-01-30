
// #include "list.h"
// void listAppend(List new, int value);
// void doListReverse(Node n, List new);

// void listReverse(List l) {
// 	List new = newList();
// 	doListReverse(l->head, new);
// }

// void doListReverse(Node n, List new) {
// 	if (n == NULL) {
// 		return;
// 	}
// 	doListReverse(n->next, new);
// 	listAppend(new, n->value);
// 	printList(new);
// }

// void listAppend(List new, int value) {
// 	if (new->head == NULL) {
// 		Node n = malloc(sizeof(struct node));
// 		n->value = value;
// 		printf("first time inserting %d!!!\n", n->value);
// 		n->next = NULL;
// 		new->head = n;
// 		return;
// 	}
// 	Node curr = new->head;
// 	while (curr->next != NULL) {
// 		curr = curr->next;
// 	}

// 	Node n = malloc(sizeof(struct node));
// 	n->value = value;
// 	printf("rec inserting %d!!!\n", n->value);
// 	n->next = NULL;
// 	curr->next = n;
// 	return;
// }

#include "list.h"
Node doListReverse(Node curr, Node last);

void listReverse(List l) {
	if (l == NULL || l->head == NULL) {
		return;
	}
	if (l->head->next == NULL) {
		return;
	}

	Node curr = l->head;
	l->head = doListReverse(curr, NULL);
}

Node doListReverse(Node curr, Node last) {
	if (curr->next == NULL) {
		curr->next = last;
		return curr;
	}
	Node s = doListReverse(curr->next, curr);
	curr->next = last;
	return s;
}
