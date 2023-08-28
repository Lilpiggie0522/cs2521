#include <stdio.h>
#include <stdlib.h>


void funApp(int a) {
    int* ptr = (int *)malloc(sizeof(int));
    *ptr = a;
    printf("fun app num is %d\n", 3 * (*ptr));
    free(ptr);

    
}