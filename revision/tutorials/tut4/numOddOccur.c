#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    return 0;
}

int odd(int arr[], int size) {
    for (int i = 0; i < size; i ++) {
        if (SetContains(s, arr[i])) {
            SetDelete(s, arr[i]);
        } else {
            SetInsert(s, arr[i]);
        }
    }
    int num = setSize(s);
    SetFree(s);
    return num;
}

int numSingleOccurrences(int arr[], int size) {
    Set already = SetNew();
    for (int i = 0; i < size; i ++) {
        if (SetContains(already, arr[i])) {
            if (SetContains(s, arr[i])) {
                SetDelete(s, arr[i]);    
            }
        } else {
            SetInsert(s, arr[i]);
            SetInsert(already, arr[i]);
        }
    }
    int num = setSize(s);
    SetFree(s);
    return num;
}