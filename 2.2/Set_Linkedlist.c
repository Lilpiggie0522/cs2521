#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

#define TRUE 1
#define FALSE 0

struct SetRep {
    struct Node* Head;
    int size;
};

struct Node {
    int num;
    struct Node* Next;
};

Set SetCreate() {
    Set s;
    if ((s = malloc(sizeof(struct SetRep))) == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    s->size = 0;
    return s;
}

void SetInsert(Set s, int n) {
    if (Member_Search(s, n) == TRUE) {
        printf("Number already in Set!\n");
        return;
    }

    struct Node* current;
    if (s->size == 0) {
        printf("size == 0, inserted beginning\n");
        current = malloc(sizeof(struct Node));
        current->num = n;
        current->Next = NULL;
        s->Head = current;
        s->size ++;
        return;
    }

    struct Node* New_Node;
    current = (s->Head);
    if (n < (current->num)) {
        New_Node = malloc(sizeof(struct Node));
        New_Node->Next = current;
        New_Node->num = n;
        s->Head = New_Node;
        s->size ++;
        return;
    }


    struct Node* Insertion_Point;
    while ((current != NULL) && (n > (current->num))) {
        Insertion_Point = current;
        printf("looping %d\n", current->num);
        current = current->Next;
    }

    printf("New_node created!\n");
    New_Node = malloc(sizeof(struct Node));
    New_Node->num = n;
    Insertion_Point->Next = New_Node;
    if (current != NULL) {
        printf("inserted in mid\n");
        New_Node->Next = current;
    } else {
        New_Node->Next = NULL;
        printf("inserted in back\n");
    }
    s->size ++;
}

int Member_Search(Set s, int n) {
    
    struct Node* current = (s->Head);
    while (current != NULL) {
        if ((current->num) == n) {
            return TRUE;
        }
        printf("search triggered\n");
        current = current->Next;
    }
    printf("search finished\n");
    return FALSE;
}

void SetShow(Set s) {
    struct Node* current = s->Head;
    printf("{");
    while (current != NULL) {
        printf("%d", current->num);
        if ((current->Next) != NULL) {
            printf(",");
        }
        current = current->Next;
    }
    printf("}");
}