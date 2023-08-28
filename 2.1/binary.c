#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX_NUM 99
int binary_search(int* array, int left, int right, int looking_for);

int main(int argc, char* argv[]) {
    int arr[MAX_NUM] = {1, 3, 4, 5, 7, 9, 11};
    int looking_for;
    scanf("%d", &looking_for);
    if (binary_search(arr, 0, 7, looking_for) == TRUE) {
        printf("%d is in array!\n", looking_for);
    } else {
        printf("%d not in array!!!\n", looking_for);
    }
    return 0;
}

int binary_search(int* array, int left, int right, int looking_for) {
    if (left > right) {
        return FALSE;
    }
    int mid = left + (right - left) / 2;
    if (array[mid] == looking_for) {
        return TRUE;
    }
    if (array[mid] > looking_for) {
        return binary_search(array, left, mid - 1, looking_for);
    }
    if (array[mid] < looking_for) {
        return binary_search(array, mid + 1, right, looking_for);
    }
    return FALSE;
}