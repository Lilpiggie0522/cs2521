#include <stdio.h>
typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))


void swap(Item items[], int i, int min);
void sort(Item items[], int lo, int hi);
void print(Item items[], int size);

int main(int argc, char *argv[]) {
    
    Item items[6] = {4, 1, 7, 3, 8, 2};
    sort(items, 0, 5);
    print(items, 6);
    return 0;
}

void sort(Item items[], int lo, int hi) {
    for (int i = lo; i < hi; i ++) {
        int smallest = i;
        for (int j = i + 1; j <= hi; j ++) {
            if (items[j] < items[smallest]) {
                smallest = j;
            }
        }
        swap(items, i, smallest);
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


// for(int i = 0; i <= hi; i ++) {
//     for (int j = lo; j < hi; j ++) {
//         bool swapped = false;
//         if (items[j] > items[j + 1]) {
//             swap(items, j, j + 1);
//             swapped = true;
//         }
//         if (swapped != true) {
//             return;
//         }
//     }
    
// }