#include <stdio.h>
#include <stdbool.h>

typedef int Item;

void swap(Item items[], int i, int min);
void sort(Item arr[], int size);
void print(Item items[], int size);

int main(int argc, char *argv[]) {
    Item items[8] = {11,1,2,4,3,5,2,9};
    sort(items, 8);
    print(items, 8);
    return 0;
}

void sort(Item arr[], int size) {
    int lo = 0;
    int hi = size - 1;
    for (int i = hi; i > lo; i --) {
        bool swapped = false;
        for (int j = lo; j < i; j ++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                swapped = true;
            }
        }
        if (swapped != true) {
            break;
        }
    }
}

// 7 1 5 4 2
// 1 5 4 2 7

void swap(Item items[], int i, int min) {
    int temp = items[i];
    items[i] = items[min];
    items[min] = temp;
}

void print(Item items[], int size) {
    for (int i = 0; i < size; i ++) {
        printf("%d\n", items[i]);
    }
}