#include <stdio.h>
#include <stdlib.h>

struct node {
    int n;
    struct node *next;
};


struct node *create_ptr(struct node *head, int n);
struct node *list_append(struct node *list, int n);
void print_list(struct node *head);


int main(int argc, char *argv[]) {
    struct node *head = create_ptr(NULL, 4);
    head = create_ptr(head, 3);
    head = create_ptr(head, 2);
    head = create_ptr(head, 1);
    head = list_append(head, 0);
    print_list(head);
    return 0;
}


struct node *create_ptr(struct node *head, int n) {
    if (head == NULL) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->n = n;
        new_node->next = NULL;
        return new_node;
    } else {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->n = n;
        new_node->next = head;
        return new_node;
    }
}

struct node *list_append(struct node *list, int n) {
    if (list == NULL) {
        return create_ptr(NULL, n);
    } else {
        list->next = list_append(list->next, n);
        return list;
    }
}

void print_list(struct node *head) {
    struct node *curr;
    curr = head;
    while (curr != NULL) {
        printf("%d\n", curr->n);
        curr = curr->next;
    }
}
