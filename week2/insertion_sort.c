#include <stdio.h>
#include <stdbool.h>


typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))

void swap(Item items[], int i, int min);
void sort(Item arr[], int size);
void print(Item items[], int size);

int main(int argc, char *argv[]) {
    Item items[8] = {41,1,7,3,8,6,5,2};
    sort(items, 8);
    print(items, 8);
    return 0;
}

void sort(Item arr[], int size) {
    int lo = 0;
    int hi = size - 1;
    for (int i = lo; i < hi; i ++) {
        int j = i + 1;
        int curr = arr[j];
        for (; j > lo; j --) {
            if (curr >= arr[j - 1]) {
                break;
            }
            arr[j] = arr[j - 1];
        }
        arr[j] = curr;
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


   