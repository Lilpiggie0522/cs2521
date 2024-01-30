#include <stdio.h>
#include <stdlib.h>

struct node {
    int n;
    struct node *next;
};

struct list {
    struct node *head;
};

struct node *create_ptr(struct node *head, int n);
void list_append(struct list *list, int n);
struct node *do_list_append(struct node *head, int n);
void print_list(struct node *head);


int main(int argc, char *argv[]) {
    struct node *head = create_ptr(NULL, 4);
    head = create_ptr(head, 3);
    head = create_ptr(head, 2);
    head = create_ptr(head, 1);
    struct list *list = malloc(sizeof(struct list));
    list->head = head;
    list_append(list, 31);
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

void list_append(struct list *list, int n) {
    do_list_append(list->head, n);
}

struct node *do_list_append(struct node *head, int n) {
    if (head == NULL) {
        return create_ptr(NULL, n);
    } else {
        head->next = do_list_append(head->next, n);
        return head;
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
