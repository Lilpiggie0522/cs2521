#include <stdio.h>
#include <stdbool.h>
typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))


void swap(Item items[], int i, int min);
void sort(Item items[], int lo, int hi);
void print(Item items[], int size);

int main(int argc, char *argv[]) {
    
    // Item items[6] = {4, 1, 7, 3, 8, 2};
    // sort(items, 0, 5);
    // print(items, 6);

    // Item items[1] = {1};
    // sort(items, 0, 0);
    // print(items, 1);

    // Item items[0] = {};
    // sort(items, 0, 0);
    // print(items, 0);

    Item items[10] = {14, 1, 7, 3, 8, 2, 13, 9, 11, 6};
    sort(items, 0, 9);
    print(items, 10);
    return 0;
}

void sort(Item items[], int lo, int hi) {
    // for (int i = lo; i < hi; i ++) {
    //     int swapped = false;
    //     for (int j = lo; j < hi; j ++) {
    //         if (items[j] > items[j + 1]) {
    //             int temp = items[j];
    //             items[j] = items[j + 1];
    //             items[j + 1] = temp;
    //             swapped = true;
    //         }
    //     }
    //     if (!swapped) {
    //         return;
    //     }
    // }
    for (int i = hi; i > lo; i --) {
        bool swapped = false;
        for (int j = lo; j < i; j++) {
            if (items[j] > items[j + 1]) {
                swap(items, j, j + 1);
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
    }
        
}
    

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