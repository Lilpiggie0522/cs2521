#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *try();
struct node *create_ptr(struct node *head, int n);
void last_node(struct node *head);

int main(int arc, char* argv[]) {
    // struct node *ptr1 = try();
    // printf("%d\n", ptr1->value);
    struct node *head = create_ptr(NULL, 4);
    head = create_ptr(head, 3);
    head = create_ptr(head, 2);
    head = create_ptr(head, 1);
    // last_node(head);

    int a = 5;
    int b = 234;
    int c = 11;
    int *pa = &a;
	int *pb = &b;
    int *pc = &c;

    pa = pb;
    pb = pc;
    b = 1188;
    
    printf("value at pb is %d\n", *pb);

}

struct node *try() {
    struct node *ptr1 = malloc(sizeof(struct node));
    ptr1->value = 1;
    ptr1->next = NULL;
    return ptr1;
}

struct node *create_ptr(struct node *head, int n) {
    if (head == NULL) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->value = n;
        new_node->next = NULL;
        return new_node;
    } else {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->value = n;
        new_node->next = head;
        return new_node;
    }
}

void last_node(struct node *head) {
    struct node *curr;
    struct node *last;
    curr = head;
    last = NULL;

    while (curr != NULL) {
        last = curr;
        printf("last before is %d\n", last->value);
        curr = curr->next;
        printf("last after is %d\n", last->value);
    }
}