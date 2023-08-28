#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 99

void sort(int* arr, int size);

int main(int argc, char* argv[]) {
//    int arr[] = {5, 7, 6, 8, 1, 4};
//    int size = 6;
    int size = 0;
    int arr[MAX_SIZE];
    while (scanf("%d", &arr[size]) != -1) {
        size ++;
    }
   sort(arr, size);
   for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);
   }
   printf("\n");
    return 0;
}

void sort(int* arr, int size) {
    int sorted = FALSE;
    while (sorted == FALSE) {
        sorted = TRUE;
        for (int i = 0; i < size - 1; i++) {
            int temp = 0;
            if (arr[i] > arr[i + 1]) {
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                sorted = FALSE;
            }
        }
    }
}