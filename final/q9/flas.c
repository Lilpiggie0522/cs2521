
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"


struct node *flas(struct node *l) {
    
    struct node *final = NULL;
    int length = 0;
    for (struct node *curr = l; curr != NULL; curr = curr->next) {
        int innerL = 0;
        struct node *temp = curr;
        // printf("curr is %d\n", curr->value);
        while (curr->next != NULL) {
            if (curr->value < curr->next->value) {
                // printf("curr in is %d next is %d\n", curr->value, curr->next->value);
                innerL ++;
                curr = curr->next;
            } else {
                break;
            }
        }
         
        if (innerL > length) {
            final = temp;
            // printf("final is %d\n", final->value);
            length = innerL;
            // printf("length is %d\n", length);
        }
    }
    return final;
}
