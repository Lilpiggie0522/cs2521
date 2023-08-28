#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

#define TRUE 1
#define FALSE 0

struct SetRep {
    int size;
    int elements[MAX_NUM];
};

Set SetCreate() {
    Set NewSet;
    // struct SetRep* NewSet;
    if ((NewSet = malloc(sizeof(struct SetRep))) == NULL) {
        fprintf(stderr, "Insufficient Memory for Set\n");
        exit(EXIT_FAILURE);
    }
    NewSet->size = 0;
    return NewSet;
}

int Member_Search(Set s, int n) {
    int left = 0;
    int right = (s->size) - 1;
    if (binary_search(s, left, right, n) == FALSE) {
        // printf("can add not in set!\n");
    }
    return binary_search(s, left, right, n);
}

int binary_search(Set s, int left, int right, int looking) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if ((s->elements)[mid] == looking) {
            return TRUE;
        }
        if (looking < (s->elements)[mid]) {
            // printf("left is %d, right is %d, mid is %d\n", left, right, mid);
            return binary_search(s, left, mid - 1, looking);
        }
        if (looking > (s->elements)[mid]) {
            // printf("left is %d, right is %d, mid is %d\n", left, right, mid);
            return binary_search(s, mid + 1, right, looking);
        }
    }
    return FALSE;
}

void SetInsert(Set s, int n) {
    if (Member_Search(s, n) == TRUE) {
        printf("Elements already in set!\n");
        return;
    }
    int left = 0;
    int right = (s->size) - 1;
    int mid = left + (right - left) / 2;
    int critical_index = 0;
    if (n < (s->elements)[mid]) {
        while ((n < (s->elements)[mid]) && (left <= right)) {
            right = mid - 1;
            mid = left + (right - left) / 2;
            // printf("checking small!\n");
        }
            critical_index = mid + 1;
            printf("index to insert is %d\n", critical_index);
            Set_insert_special(s, critical_index, n);
            return;
    } else {
         while ((n > (s->elements)[mid]) && left <= right) {
            left = mid + 1;
            mid = left + (right - left) / 2;
            // printf("checking big!\n");
        }
            critical_index = mid;
            Set_insert_special(s, critical_index, n);
            // printf("index to insert is %d\n", critical_index);
            return;
    }
    
}

void Set_insert_special(Set s, int critical_index, int n) {
    int temp = 0;
    int temp1 = 0;
    for (int i = critical_index; i < (s->size) + 1; i ++) {
        if (i == critical_index) {
            temp = (s->elements)[i];
            temp1 = (s->elements)[i + 1];
            (s->elements)[i] = n;
            i ++;
        } else {
            (s->elements)[i] = temp;
            temp = temp1;
            if (i < (s->size) - 1) {
                temp1 = (s->elements)[i + 1];
            }
        }
    }
    s->size ++;
}

void SetDeletion(Set s, int n) {
    int left = 0;
    int right = (s->size) - 1;
    if (index_finding(s, left, right,n) == FALSE) {
        printf("Elements not in set! Cannot delete\n");
        return;
    }
    int critical_index = index_finding(s, left, right, n);
    printf("critical index is %d\n", critical_index);
    for (int i = critical_index; i < (s->size) - 1; i ++) {
        (s->elements)[i] = (s->elements)[i + 1];
    }
    s->size --;
}

int index_finding(Set s, int left, int right, int looking) {
      while (left <= right) {
        int mid = left + (right - left) / 2;
        if ((s->elements)[mid] == looking) {
            return mid;
        }
        if (looking < (s->elements)[mid]) {
            // printf("left is %d, right is %d, mid is %d\n", left, right, mid);
            return index_finding(s, left, mid - 1, looking);
        }
        if (looking > (s->elements)[mid]) {
            // printf("left is %d, right is %d, mid is %d\n", left, right, mid);
            return index_finding(s, mid + 1, right, looking);
        }
    }
    return FALSE;
}
void SetShow(Set s) {
    printf("{");
    for (int i = 0; i < s->size; i ++) {
        printf("%d", (s->elements)[i]);
        if (i < s->size - 1) {
            printf(",");
        }
    }
    printf("}");
}

