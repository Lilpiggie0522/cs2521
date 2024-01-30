#include <stdio.h>
typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))


void swap(Item items[], int i, int min);
void sort(Item items[], int lo, int hi);
void print(Item items[], int size);

int main(int argc, char *argv[]) {
    
    Item items[8] = {1, 7, 5, 4, 3, 5, 8, 9};
    sort(items, 0, 7);
    print(items, 8);
    return 0;
}

void sort(Item items[], int lo, int hi) {
    for (int i = lo; i < hi; i ++) {
        int min = i;
        int j = i + 1;
        for (; j <= hi; j++) {
            printf("entering condition\n");
            if (items[j] < items[min]) {
                min = j;
            }
        }
        swap(items, i, min);
    }
}
// 7 1 4 3 2 
// 1 7 4 3 2


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