#include <stdio.h>
void sum ();


int main(int argc, char* argv[]) {
    sum();
    return 0;
}

void sum () {
    int sum = 0;
    int temp;
    while (scanf("%d", &temp) != -1) {
        sum +=temp;
    }
    printf("%d\n", sum);
}