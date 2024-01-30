#include <stdio.h>
#include <stdlib.h>

typedef int Item;

#define key(A) (A)
#define leq(A, B) (key(A) <= key(B))

void print(Item items[], int size);
void swap(Item items[], int i, int j);
void quickSort(Item arr[], int lo, int hi);
int partition(Item arr[], int lo, int hi);

int main(int argc, char *argv[]) {
        Item arr[6] = {7, 1, 4, 5, 3, 8}; 
        // print(arr, 6);
        int lo = 0;
        int hi = 5;
        quickSort(arr, lo, hi);
        print(arr, 6);
        return 0;
}


void quickSort(Item arr[], int lo, int hi) {
    if (lo >= hi) {
        return;
    }
    int j;
    j = partition(arr, lo, hi);
    quickSort(arr, lo, j);
    quickSort(arr, j + 1, hi);
}

int partition(Item arr[], int lo, int hi) {
    int pvt = arr[lo];
    int i = lo, j = hi;
    while (i < j) {
        while (arr[i] <= pvt) {
            i ++;
        }

        while (arr[j] > pvt) {
            j --;
        }
        if (i < j) {
            swap(arr, i, j);
        }
    }
    swap(arr, lo, j);
    return j;
    
}



void print(Item items[], int size) {
    for (int i = 0; i < size; i ++) {
        printf("%d\n", items[i]);
    }
}

void swap(Item items[], int i, int j) {
    int temp = items[i];
    items[i] = items[j];
    items[j] = temp;
}