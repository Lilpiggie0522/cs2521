#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
}; 

// int main(int argc, char* argv[]) {
//     return 0;
// }

int length_check(struct node *head) {
    int length = 0;
    struct node *current = (struct node *)malloc(sizeof(struct node));
    current = head;
    while (current != NULL) {
        length ++;
        current = current->next;
    }
    free(current);
    return length;
}

int length_check_2521(struct node *head) {
    struct node* current = (struct node*)malloc(sizeof(struct node*));
    int length = 0;
    for (current = head; current != NULL; current = current->next) {
        length ++;
    }
    return length;
    free(current);
}

int length_check_recursion(struct node* head) {
    if (head == NULL) return 0;
    // struct node* current = (struct node*)malloc(sizeof(struct node));
    return 1 + length_check_recursion(head->next);
}