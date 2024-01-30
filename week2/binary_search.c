#include <stdio.h>
int search (int arr[], int size, int num);


int main (int argc, char *argv[]) {
    int array[8] = {1, 3, 7, 9, 11, 13, 17, 222};
    int num;
    int valid;
    while ((valid = scanf("%d", &num)) != -1) {
        scanf("%d", &num);
    }
    ;
    int contains = search(array, 8, num);
    if (contains == -1) {
        printf("Num not included!\n");
    } else {
        printf("Num is at index %d\n", contains);
    }
    return 0;
}

int search (int arr[], int size, int num) {
    int lo = 0;
    int hi = size - 1;

    while (lo <= hi) {
        printf("once!\n");
        int mid = (lo + hi) / 2;
        if (num < arr[mid]) {
            hi = mid - 1;
        } else if (num > arr[mid]) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}