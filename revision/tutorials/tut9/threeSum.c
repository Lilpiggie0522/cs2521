#include <stdio.h>

bool threeSum(int arr[], int value, int size) {
    Hashtable h = HashtableNew();

    for (int i = 0; i < size; i ++) {
        if (HashtableContains(h, value - arr[i])) {
            HashTableFree(h);
            return true;
        }

        for (int j = 0; j < i; j ++) {
            HashTableInsert(h, arr[i] + arr[j], 0);
        }
    }
}