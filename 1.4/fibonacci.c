#include <stdio.h>
int fibonacci(int n);

int main(int argc, char* argv[]) {
    int nth;
    scanf("%d", &nth);
    printf("%dth fb is %d\n", nth, fibonacci(nth));
    return 0;
}

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 1;
    }
    return fibonacci(n - 2) + fibonacci(n - 1);
}