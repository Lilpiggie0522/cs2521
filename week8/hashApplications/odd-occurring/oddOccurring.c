
#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"

int oddOccurring(int arr[], int size) {
	HashTable ht = HashTableNew();
	for (int i = 0; i < size; i ++) {
		int count = HashTableGetOrDefault(ht, arr[i], 0);
		HashTableInsert(ht, arr[i], count + 1);
	}
	
	int counter = 0;
	for (int i = 0; i < size; i ++) {
		if (HashTableGetOrDefault(ht, arr[i], 0) % 2 == 1) {
			counter ++;
		}
		HashTableDelete(ht, arr[i]);
	}
	HashTableFree(ht);
	return counter;
}

