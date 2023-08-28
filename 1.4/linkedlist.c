#include <stdio.h>
#include "linkedlist.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    struct node *node2 = (struct node * )malloc(sizeof(struct node));
    struct node *node3 = (struct node *)malloc(sizeof(struct node));
    head->data = 12;
    node1->data = 13;
    node2->data = 14;

    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    printf("Length of this list in recursion is %d\n", length_check_recursion(head));
    free(head);
    free(node1);
    free(node2);
    free(node3);
    return 0;
}

