#include <stdio.h>
#include <stdlib.h>


struct node {
	int value;
	struct node *next;
};

int listLength(struct node *l);


int main(int argc, char *argv[]) {
    struct node *ptr = malloc(sizeof(struct node));
    ptr->value = 1;
    ptr->next = NULL;

    struct node *ptr1 = malloc(sizeof(struct node));
    ptr1->value = 2;
    ptr1->next = NULL;

    struct node *ptr2 = malloc(sizeof(struct node));
    ptr2->value = 3;
    ptr2->next = NULL;

    struct node *ptr3 = malloc(sizeof(struct node));
    ptr3->value = 4;
    ptr3->next = NULL;

    ptr->next = ptr1;
    ptr1->next = ptr2;
    ptr2->next = ptr3;
    ptr3->next = NULL;
    
    printf("length is %d\n", listLength(ptr));

    return 0;
}

int listLength(struct node *l) {
    if (l == NULL) {
        return 0;
    } else {
        return 1 + listLength(l->next);
    }
}

