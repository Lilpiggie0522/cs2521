#include <stdio.h>
#include "library.h"


int main(int argc, char* argv[]) {
    printf("%d + %d = %d\n", 4, 5, add(4, 5));
    printf("%d - %d = %d\n", 4, 5, sub(4, 5));
    return 0;
}