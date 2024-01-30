#include <stdio.h>
#include <stdlib.h>



struct node {
	int value;
	struct node *next;
};

struct list {
	struct node *head;
};

struct node *Create_Node (struct node *head, int value);
struct node *listDelete(struct list *list1, int value);

int main (int argc, char* argv[]) {
    // int* a = malloc(5 * sizeof(int));
    // for (int i = 0; i < 5; i++) {
	// 	a[i] = 42;
	// }
    //  for (int i = 0; i < 5; i++) {
	// 	printf("%d\n", a[i]);
	// }


    // struct node *last = NULL;
    // struct node *head = NULL;
    // int i = 0;
    // for (i = 0; i < 5; i ++) {
        
    //     struct node *nd = malloc(sizeof(struct node));
    //     nd->value = i;
    //     nd->next = NULL;
    //     if (last != NULL) {
    //         last->next = nd;
    //     }
    //     last = nd;
    //     if (i == 0) {
    //         head = nd;
    //     }
    // }

    // struct node *curr = NULL;
    // curr = head;
    // while (curr != NULL) {
    //     printf("%d\n", curr->value);
    //     curr = curr->next;
    // }

    // for (struct node *now = head; now != NULL; now = now->next) {
    //     printf("%d\n", now->value);
    // }
    struct list *list1 = malloc(sizeof(struct list));

    list1->head = Create_Node(NULL, 4);
    list1->head = Create_Node(list1->head, 3);
    list1->head = Create_Node(list1->head, 2);
    list1->head = Create_Node(list1->head, 1);
    struct node *curr = list1->head;
    // while (curr != NULL) {
    //     printf("%d\n", curr->value);
    //     curr = curr->next;
    // }
    list1->head = listDelete(list1, 1);
    curr = list1->head;
    while (curr != NULL) {
        printf("%d\n", curr->value);
        curr = curr->next;
    }
}

struct node *Create_Node (struct node *head, int value) {
    if (head == NULL) {
        struct node *New = malloc(sizeof(struct node));
        New->value = value;
        New->next = NULL;
        return New;
    } else {
        struct node *New = malloc(sizeof(struct node));
        New->value = value;
        New->next = head;
        return New;
    }
}

struct node *listDelete(struct list *list1, int value) {
    if (list1->head == NULL) {
        return NULL;
    } else {
        struct node *curr = list1->head;
        struct node *last = NULL;
        while (curr != NULL) {
            if (curr->value == value) {
                if (last == NULL) {
                    struct node *new = curr->next;
                    free(curr);
                    return new;
                } else {
                    last->next = curr->next;
                    free(curr);
                    return list1->head;
                }
            }
            last = curr;
            curr = curr->next;
        }
    }
    return list1->head;
}