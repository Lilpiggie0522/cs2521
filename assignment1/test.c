#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct cmp {
    char *token;
};
void func(struct cmp *new);
int main(int argc, char *argv[]) {
    struct cmp *new = malloc(sizeof(struct cmp));

    new->token = malloc(sizeof(char));
    new->token = malloc(sizeof(char));
    printf("size of token is %lu\n", sizeof(new->token));
}




// File f = FileOpenToRead(inputFilename);
	// char token[MAX_TOKEN_LEN];
	// struct tokenList *List = malloc(sizeof(struct tokenList));
	// List->size = 0;
	// List->head = NULL;
	// while (FileReadToken(f, token)) {
	// 	// printf("calculating size!\n");
	// 	List->head = insertToken(List->head, token, List);
	// }

	// printf("Token size is %d\n", List->size);
	// int size = List->size;

    // FileClose(f);
	// freeToken(List->head);
	// free(List);


    // old inefficient code
	/* struct stack *s = malloc(sizeof(struct stack));
	s->size = 0;
	s->head = NULL;
	while (FileReadToken(f, token)) {
		bool found = false;
		s = findToken(tree, token, &found, s);
	}
	int length = s->size + 1;
	printf("size of array is %d\n", length);
	char *arr = malloc(sizeof(char) * length);
	int index = 0;
	printList(s->head, arr, &index);
	arr[index] = '\0';
	printf("arr[0] is %c\n", arr[0]);
	printf("arr[1] is %c\n", arr[1]);
	printf("arr[2] is %c\n", arr[2]);
	
	
	
	freeList(s->head);
	FileClose(f);
	return arr; */


    // old inefficient code
/* static struct stack *findToken(struct huffmanTree *tree, char *token, bool *found, struct stack *s) {
	if (tree == NULL) {
		// printf("given tree empty, cannot encode!\n");
		return s;
	}

	if (tree->left == NULL && tree->right == NULL && (strcmp(tree->token, token) == 0)) {
		*found = true;
		return s;
	}

	s = insertList(s, 0);
	s = findToken(tree->left, token, found, s);
	if (*found == false) {
		s = deleteList(s);
	}

	if (*found == false) {
		s = insertList(s, 1);
		s = findToken(tree->right, token, found, s);
		if (*found == false) {
			s = deleteList(s);
		}
	}
	
	return s;
}

static struct stack *insertList(struct stack *s, int num) {
	if (s->head == NULL) {
		struct list *newList = malloc(sizeof(struct list));
		newList->next = NULL;
		newList->num = num;
		s->head = newList;
		s->size ++;
		return s;
	}
	struct list *newList = malloc(sizeof(struct list));
	newList->next = s->head;
	newList->num = num;
	s->head = newList;
	s->size ++;
	return s;
}

static struct stack *deleteList (struct stack *s) {
	struct list *old = s->head;
	s->head = s->head->next;
	free(old);
	return s;
}

static void freeList(struct list *l) {
	if (l == NULL) {
		return;
	}
	freeList(l->next);
	free(l);
}

static void printList(struct list *l, char *arr, int *index) {
	if (l == NULL) {
		// printf("List empty!\n");
		return;
	}
	printList(l->next, arr, index);
	// printf("%d\n", l->num);
	if (l->num == 0) {
		arr[*index] = '0';
		(*index) ++;
	} else if (l->num == 1) {
		arr[*index] = '1';
		(*index) ++;
	}
} */




// static struct token *insertToken(struct token *l, char *token, struct tokenList *List) {
// 	if (l == NULL) {
// 		struct token *newToken = malloc(sizeof(struct token));
// 		newToken->token = strdup(token);
// 		newToken->next = NULL;
// 		List->size ++;
// 		return newToken;
// 	}
// 	if (strcmp(l->token, token) == 0) {
// 		// printf("same token\n");
// 		return l;
// 	}
// 	if (l->next == NULL) {
// 		struct token *newToken = malloc(sizeof(struct token));
// 		newToken->token = strdup(token);
// 		newToken->next = NULL;
// 		l->next = newToken;
// 		List->size ++;
// 		return l;
// 	}
// 	l->next = insertToken(l->next, token, List);
// 	return l;
// }

// void freeToken(struct token *l) {
// 	if (l == NULL) {
// 		return;
// 	}
// 	freeToken(l->next);
// 	free(l->token);
// 	free(l);
// }