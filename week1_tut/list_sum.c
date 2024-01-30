#include <stdio.h>
#include <stdlib.h>

struct node {
    int n;
    struct node *next;
};

struct node *create_ptr(struct node *head, int n);
int summing_list(struct node *head);

int main(int argc, char *argv[]) {
    struct node *head = create_ptr(NULL, 4);
    head = create_ptr(head, 3);
    head = create_ptr(head, 2);
    head = create_ptr(head, 1);
    int total = summing_list(head);
    printf("%d\n", total);
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

int summing_list(struct node *head) {
    if (head == NULL) {
        return 0;
    } else {
        return head->n + summing_list(head->next);
    }
}

