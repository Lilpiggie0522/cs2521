#include <stdio.h>

int main(int argc, char* argv[]) {
    char gg[] = "pig";
    char* gg_Ptr = gg;
    char* gg1 = "pigg";
    printf("gg is %c\n", *gg_Ptr);
    printf("gg1 is %s\n", gg1);

    char* xx[] = {"pig", "dc"};
    char** dd = xx;
    printf("xx[0] is %c\n", (*xx)[2]);
    printf("dd[1] is %c\n", (*dd)[0]);

    int arr[] = {3, 1, 4, 5, 6};
    int* arr1 = arr;
    printf("arr[2] is %d\n", arr1[2]);
}

