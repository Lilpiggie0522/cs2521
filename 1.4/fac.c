#include <stdio.h>
int fac (int n);
int fibo (int n);

int main (int argc, char* argv[]) {
    int n;
    scanf("%d", &n);
    printf("%d factorial is %d\n", n, fac(n));
    printf("%d fib is %d\n", n, fibo(n));
}

int fac (int n) {
    if(n == 0) return 1;
    return n * fac(n - 1);
}

int fibo (int n) {
    if (n == 1) return 1;
    if (n == 2) return 1;
    return fibo(n - 2) + fibo(n - 1);
}