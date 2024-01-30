#include <stdio.h>
#include <stdlib.h>

typedef int Item;

#define key(A) (A)
#define leq(A, B) (key(A) <= key(B))

void print(Item items[], int size);
void mergeSort(Item arr[], int lo, int hi);
void mergeArr(Item items[], int lo, int mid, int hi);

int main(int argc, char *argv[]) {
        Item arr[6] = {7, 1, 4, 5, 3, 8}; 
        // print(arr, 6);
        int lo = 0;
        int hi = 5;
        mergeSort(arr, lo, hi);
        print(arr, 6);
        return 0;
}


void mergeSort(Item arr[], int lo, int hi) {
    if (lo >= hi) {
        return;
    }
    int mid = (hi + lo) / 2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid + 1, hi);
    mergeArr(arr, lo, mid, hi);
}



void mergeArr(Item arr[], int lo, int mid, int hi) {
    int *temp = malloc(sizeof(int) * (hi - lo + 1));
    int i = lo, j = mid + 1, k = 0;
    while (i <= mid && j <= hi) {
        printf("comparing!\n");
        if (arr[i] <= arr[j]) {
            temp[k ++] = arr[i ++];
        } else {
            temp[k ++] = arr[j ++];
        }
    }
    while (i <= mid) {
        temp[k ++] = arr[i ++];
    }
    while (j <= hi) {
        temp[k ++] = arr[j ++];
    }

    for (int i = lo, k = 0; i <= hi; i ++) {
        arr[i] = temp[k];
        k ++;
    }
    free(temp);
}


void print(Item items[], int size) {
    for (int i = 0; i < size; i ++) {
        printf("%d\n", items[i]);
    }
}