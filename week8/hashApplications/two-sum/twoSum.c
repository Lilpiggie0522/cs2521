
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"

bool twoSum(int arr[], int size, int sum) {
	HashTable ht = HashTableNew();
	for (int i = 0; i < size; i ++) {
		if (HashTableContains(ht, sum - arr[i])) {
			HashTableFree(ht);
			return true;
		}
		HashTableInsert(ht, arr[i], 0);
	}

	HashTableFree(ht);
	return false;



	/* for (int i = 0; i < size; i ++) {
		for (int j = i + 1; j < size; j ++) {
			if (sum - arr[i] == arr[j]) {
				return true;
			}
		}
	}
	return false; */
}

