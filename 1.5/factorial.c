#include <stdio.h>
int factorial(int n);


int main(int argc, char* argv[]) {
    int a;
    scanf("%d", &a);
    printf("%d factorial is %d\n", a, factorial(a));
    return 0;
}

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}