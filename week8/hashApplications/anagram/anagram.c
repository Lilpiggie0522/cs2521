
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"

static HashTable strToHash(char *str);

bool anagram(char *s, char *t) {
	// TODO
	HashTable ht1 = strToHash(s);
	HashTable ht2 = strToHash(t);

	int size1 = HashTableSize(ht1);
	int size2 = HashTableSize(ht2);
	if (size1 != size2) {
		HashTableFree(ht1);
		HashTableFree(ht2);
		return false;
	}

	for (int i = 0; s[i] != '\0'; i ++) {
		int count1 = HashTableGet(ht1, s[i]);
		int count2 = HashTableGetOrDefault(ht2, s[i], 0);
		if (count1 != count2) {
			HashTableFree(ht1);
			HashTableFree(ht2);
			return false;
		}
	}
	HashTableFree(ht1);
	HashTableFree(ht2);
	return true;
}

static HashTable strToHash(char *str) {
	HashTable ht = HashTableNew();
	for (int i = 0; str[i] != '\0'; i ++) {
		int count = HashTableGetOrDefault(ht, str[i], 0);
		HashTableInsert(ht, str[i], count + 1);
	}
	return ht;
}


