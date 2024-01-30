#include <stdio.h>
int get_fib(int n);

int main(int argc, char *argv[]) {
    printf("%d\n", get_fib(2));
    return 0;
}

int get_fib(int n) {
    if (n <= 2) {
        return 1;
    } else {
        return get_fib(n - 1) + get_fib(n - 2);
    }
}