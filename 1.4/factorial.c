#include <stdio.h>
int factorial(int n);

int main (int argc, char* argv[]) {
    printf("%d factorial is %d\n", 5, factorial(5));
    return 0;
}


int factorial (int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}