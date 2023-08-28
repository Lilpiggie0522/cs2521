#include <stdio.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

int isEven(int num);
void test_even();

int main (int argc, char* argv[]){
    test_even();
    return 0;
}

int isEven(int num) {
    if (num % 2 == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void test_even() {
    assert(isEven(2) == TRUE);
    printf("Even\n");
    assert(isEven(3) == FALSE);
    printf("Odd\n");
}