#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool twoSum(int *arr, int value, int size);

int main(int argc, char *argv[]) {
    int arr[4] = {3, 2, 1, 7 };
    bool re = twoSum(arr, 34, 4);
    printf("contains: %d\n", re);
    return 0;
}

bool twoSum(int *arr, int value, int size) {
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j ++) {
            if (j != i) {
                if (arr[j] + arr[i] == value) {
                    return true;
                }
            }
        }
    }
    return false;
}