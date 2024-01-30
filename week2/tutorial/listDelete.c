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

struct node *DoDelete(struct node *head, int value);
struct list *listDelete(struct list *l, int value);
void list_print(struct node *head);

int main(int argc, char *argv[]) {
    struct node *ptr = malloc(sizeof(struct node));
    ptr->value = 0;
    ptr->next = NULL;

    struct node *ptr1 = malloc(sizeof(struct node));
    ptr1->value = 2;
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
    list_print(l->head);
    l = listDelete(l, 0);
    list_print(l->head);

    
    return 0;
}

struct list *listDelete(struct list *l, int value) {
    l->head = DoDelete(l->head, value);
    return l;
}

struct node *DoDelete(struct node *head, int value) {
    if (head == NULL) {
        return NULL;
    } else {
        if (head->value == value) {
                printf("triggered!\n");
                struct node *temp = head->next;
                free(head);
                return temp;
        } else {
            head->next = DoDelete(head->next, value);
            return head;
        }
    }
}

 void list_print(struct node *head) {
    struct node *curr = head;
    struct node *last = NULL;
    while (curr != NULL) {
        printf("%d\n", curr->value);
        last = curr;
        curr = curr->next;
        // printf("%d\n", last->value);
    }
}



