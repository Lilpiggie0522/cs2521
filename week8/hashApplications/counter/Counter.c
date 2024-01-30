
#include <stdio.h>
#include <stdlib.h>

#include "Counter.h"
#include "HashTable.h"

struct counter {
	HashTable ht;
};

Counter CounterNew(void) {
	Counter c = malloc(sizeof(struct counter));
	c->ht = HashTableNew();
	return c;
}

void CounterFree(Counter c) {
	HashTableFree(c->ht);
	free(c);
}

void CounterAdd(Counter c, int item) {
	int count = HashTableGetOrDefault(c->ht, item, 0);
	HashTableInsert(c->ht, item, count + 1);
	return;
}

int CounterGet(Counter c, int item) {
	return HashTableGetOrDefault(c->ht, item, 0);
}