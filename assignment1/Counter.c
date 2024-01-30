// Implementation of the Counter ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Counter.h"

struct counter {
	int numTokens;
	struct Node *root;
};

struct Node {
	char *token;
	int freq;
	struct Node *left;
	struct Node *right;
};

struct Node *FreeNodes(struct Node *curr);
struct Node *insertRecurse(struct Node *curr, char *token, Counter c);
int searchToken(struct Node *curr, char *token);
void traverseNodes(struct Node *curr, int *i, struct item *arr);

Counter CounterNew(void) {
	Counter c = malloc(sizeof(struct counter));
	if (c == NULL) {
		fprintf(stderr, "Not enough memory to be allocated!\n");
		return NULL;
	}
	c->numTokens = 0;
	c->root = NULL;
	return c;
}

void CounterFree(Counter c) {
	struct Node *curr = c->root;
	c->root = FreeNodes(curr);
	free(c);
}

struct Node *FreeNodes(struct Node *curr) {
	if (curr == NULL) {
		return NULL;
	}
	curr->left = FreeNodes(curr->left);
	curr->right = FreeNodes(curr->right);
	free(curr->token);
	free(curr);
	return NULL;
}



void CounterAdd(Counter c, char *token) {
	
	c->root = insertRecurse(c->root, token, c);
}

struct Node *insertRecurse(struct Node *curr, char *token, Counter c) {
	if (curr == NULL) {
		struct Node *newNode = malloc(sizeof(struct Node));
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->token = strdup(token);
		newNode->freq = 1;
		c->numTokens += 1;
		return newNode;
	}
	if (strcmp(token, curr->token) < 0) {
		curr->left = insertRecurse(curr->left, token, c);
	} else if (strcmp(token, curr->token) == 0) {
		curr->freq ++;
	} else {
		curr->right = insertRecurse(curr->right, token, c);
	}
	return curr;
}


int CounterNumItems(Counter c) {
	if (c == NULL) {
		return 0;
	}
	return c->numTokens;
}

int CounterGet(Counter c, char *token) {
	if (c == NULL) {
		return 0;
	}
	return searchToken(c->root, token);
}

int searchToken(struct Node *curr, char *token) {
	if (curr == NULL) {
		return 0;
	}
	if (strcmp(token, curr->token) < 0) {
		return searchToken(curr->left, token);
	} else if (strcmp(token, curr->token) > 0) {
		return searchToken(curr->right, token);
	} else {
		return curr->freq;
	}
}

struct item *CounterItems(Counter c, int *numItems) {
	*numItems = CounterNumItems(c);
	struct item *arr = calloc(*numItems, sizeof(struct item));
	int i = 0;
	traverseNodes(c->root, &i, arr);
	return arr;
}

void traverseNodes(struct Node *curr, int *i, struct item *arr) {
	if (curr == NULL) {
		return;
	}
	arr[*i].token = strdup(curr->token);
	arr[*i].freq = curr->freq;
	(*i) ++;
	traverseNodes(curr->left, i, arr);
	traverseNodes(curr->right, i, arr);
}
