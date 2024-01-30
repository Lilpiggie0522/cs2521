#include <stdio.h>


int factorial(int n);

int main(int argc, char *argv[]) {
    printf("%d\n", factorial(3));
    return 0;
}

int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}