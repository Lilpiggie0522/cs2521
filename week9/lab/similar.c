
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"

bool areSimilarStrings(char *s1, char *s2);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <string 1> <string 2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	bool result = areSimilarStrings(argv[1], argv[2]);
	printf("The strings %s similar\n", result ? "are" : "are not");
	return EXIT_SUCCESS;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Returns true if two strings are similar, and false otherwise. Two strings s1
 * and s2 are similar if, for each character in s1, it is possible to *uniquely*
 * replace it by another character (possibly itself) such that, after all
 * replacements are done to s1, we end up with s2. For example, the strings
 * "adt" and "bst" are similar, but "adt" and "dcc" are not.
 */

bool areSimilarStrings(char *s1, char *s2) {
	HashTable ht = HashTableNew();
	for (int i = 0; s1[i] != '\0'; i ++) {
		// s1[i] = s2[i];
		
		if (HashTableContains(ht, s1[i]) && HashTableGet(ht, s1[i]) != s2[i]) {
			HashTableFree(ht);
			return false;
		}
		HashTableInsert(ht, s1[i], s2[i]);
	}

	HashTable ht2 = HashTableNew();
	for (int i = 0; s2[i] != '\0'; i ++) {
		// s1[i] = s2[i];
		
		if (HashTableContains(ht2, s2[i]) && HashTableGet(ht2, s2[i]) != s1[i]) {
			HashTableFree(ht);
			HashTableFree(ht2);
			return false;
		}
		HashTableInsert(ht2, s2[i], s1[i]);
	}

	HashTableFree(ht);
	HashTableFree(ht2);
	return true;
}

// a g h s1
// b q h s2

// s2 using s1
// s2 = 




// a b a
// 
// c d e

// a b a
// c d e
