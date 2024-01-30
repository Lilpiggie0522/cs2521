#include <stdio.h>
#include <stdbool.h>


typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))

void swap(Item items[], int i, int min);
void sort(Item arr[], int size);
void print(Item items[], int size);

int main(int argc, char *argv[]) {
    Item items[6] = {4, 1, 7, 3, 8, 2};
    sort(items, 6);
    print(items, 6);
    return 0;
}

void sort(Item arr[], int size) {
   Item lo = 0;
   Item hi = size - 1;
   for (int i = lo + 1; i <= hi; i ++) {
    Item curr = arr[i];
    int j = i;
    for (j = i; j > lo; j --) {
        if (!less(curr, arr[j - 1])) {
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
