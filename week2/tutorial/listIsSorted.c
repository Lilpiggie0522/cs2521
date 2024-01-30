#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int value;
	struct node *next;
};

struct list {
	struct node *head;
};


bool listIsSorted(struct list *l);
bool check(struct node *l);

int main(int argc, char *argv[]) {
    struct node *ptr = malloc(sizeof(struct node));
    ptr->value = 0;
    ptr->next = NULL;

    struct node *ptr1 = malloc(sizeof(struct node));
    ptr1->value = 3;
    ptr1->next = NULL;

    struct node *ptr2 = malloc(sizeof(struct node));
    ptr2->value = 2;
    ptr2->next = NULL;

    struct node *ptr3 = malloc(sizeof(struct node));
    ptr3->value = 3;
    ptr3->next = NULL;

    ptr->next = ptr1;
    ptr1->next = ptr2;
    ptr2->next = ptr3;
    ptr3->next = NULL;

    struct list *l = malloc(sizeof(struct list));
    l->head = ptr;
    
    if (listIsSorted(l) == true) {
        printf("yes sorted!\n");
    } else {
        printf("No not sorted!\n");
    }
    
    return 0;
}

bool listIsSorted(struct list *l) {
    if (check(l->head) == true) {
        return true;
    } else {
        return false;
    }
}

bool check(struct node *l) {
    if (l->next == NULL) {
        return true;
    } else {
        if (l->value <= l->next->value) {
            return true && check(l->next);
        } else {
            return false;
        }
    }
}