// Implementation of the Huffman module

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Counter.h"
#include "File.h"
#include "huffman.h"

struct list {
	int num;
	struct list *next; 
};

struct stack {
	int size;
	struct list *head;
};

struct token {
	char *token;
	struct token *next;
};

struct tokenList {
	int size;
	struct token *head;
};

struct tokenInfo {
	char *token;
	char *encoding;
};

//	task 1
static char *traverseTree(struct huffmanTree *tree, char *encoding, File fileToWrite);

//	task 3
static void mergeSort(struct item *counterItems, int lo, int hi);
static void merge(struct item *counterItems, int lo, int mid, int hi);
struct huffmanTree *createNode();
static struct huffmanTree *combine(struct huffmanTree *node1, struct huffmanTree *node2);
static struct huffmanTree *makeCopy(struct huffmanTree *node);
static void checkMin(struct huffmanTree **arr, int numItems);
static void freeCounterItems(struct item *counterItems, int numItems);

//	task 4
int findHowManyTokens(struct huffmanTree *tree);
int bstToken(struct tokenInfo *encodingArr, char *token, int *size);
struct stack *findPath(struct huffmanTree *tree, char *token, struct stack *s, bool *found);

static void getEncodingStr(struct list *l, char *arr, int *index);
void bstInsert(struct tokenInfo *encodingArr, char *token, char *encoding, int *size);

static struct stack *insertList(struct stack *s, int num);
static struct stack *deleteList (struct stack *s);
void freeStackList(struct list *l);
void strCopy(char *source, char *destination, int index);

void freeEncodingArr(struct tokenInfo *encodingArr, int size);
// Task 1
void decode(struct huffmanTree *tree, char *encoding, char *outputFilename) {
	File f = FileOpenToWrite(outputFilename);
	
	while (encoding[0] != '\0') {
		encoding = traverseTree(tree, encoding, f);
	}
	FileClose(f);
}

static char *traverseTree(struct huffmanTree *tree, char *encoding, File fileToWrite) {
	if (tree->left == NULL && tree->right == NULL) {
		FileWrite(fileToWrite, tree->token);
		return encoding;
	}
	int i = 0;

	if (encoding[i] == '0') {
		encoding = &(encoding[i + 1]);
		return traverseTree(tree->left, encoding, fileToWrite);
	} else if (encoding[i] == '1') {
		encoding = &(encoding[i + 1]);
		return traverseTree(tree->right, encoding, fileToWrite);
	} else {
		return encoding;
	}
	
}

// Task 3
struct huffmanTree *createHuffmanTree(char *inputFilename) {
	File inputFile = FileOpenToRead(inputFilename);
	Counter c = CounterNew();
	char token[MAX_TOKEN_LEN];
	while (FileReadToken(inputFile, token)) {
		CounterAdd(c, token);
	}
	int numItems;
	struct item *counterItems = CounterItems(c, &numItems);
	mergeSort(counterItems, 0, numItems - 1);
	
	struct huffmanTree **arr = malloc(sizeof(struct huffmanTree *) * numItems);
	for (int i = 0; i < numItems; i ++) {
		struct huffmanTree *new = createNode();
		new->token = strdup(counterItems[i].token);
		new->freq = counterItems[i].freq;
		arr[i] = new;
	}
	
	for (int i = 0; i < numItems; i ++) {
		if (i == 0) {
			struct huffmanTree *combined = combine(arr[i], arr[i + 1]);
			struct huffmanTree *node = makeCopy(arr[i]);
			struct huffmanTree *node1 = makeCopy(arr[i + 1]);
			combined->left = node;
			combined->right = node1;

			free(arr[i]->token);
			free(arr[i]);
			arr[i] = NULL;

			free(arr[i + 1]->token);
			free(arr[i + 1]);
			arr[i + 1] = NULL;

			arr[i + 1] = combined;
			i ++;
		} else {
			checkMin(arr, numItems);
		}
	}
	struct huffmanTree *tree = NULL;
	for (int i = 0; i < numItems; i ++) {
		if (arr[i] != NULL) {
			tree = arr[i];
			break;
		}
	}

	free(arr);
	FileClose(inputFile);
	CounterFree(c);
	freeCounterItems(counterItems, numItems);
	free(counterItems);
	return tree;
}

static struct huffmanTree *combine(struct huffmanTree *node1, struct huffmanTree *node2) {
	struct huffmanTree *new = malloc(sizeof(struct huffmanTree));
	new->token = malloc(sizeof(char) * 4);
	strcpy(new->token, "");
	new->freq = node1->freq + node2->freq;
	new->left = NULL;
	new->right = NULL;
	return new;
}

static struct huffmanTree *makeCopy(struct huffmanTree *node) {
	struct huffmanTree *new = malloc(sizeof(struct huffmanTree));
	new->token = strdup(node->token);
	new->freq = node->freq;
	new->left = node->left;
	new->right = node->right;
	return new;
}

static void checkMin(struct huffmanTree **arr, int numItems) {
	int counter = 0;
	for (int i = 0; i < numItems; i ++) {
		if (arr[i] != NULL) {
			counter ++;
		}
	}
	if (counter < 2) {
		return;
	}
	int minIndex = 0;
	for (int i = 0; i < numItems; i ++) {
		if (arr[i] != NULL) {
			minIndex = i;
			break;
		}
	}
	struct huffmanTree *min = arr[minIndex];
	struct huffmanTree *node = NULL;
	struct huffmanTree *node1 = NULL;
	

	for (int i = 0; i < numItems; i ++) {
		if (arr[i] != NULL && (arr[i]->freq < min->freq)) {
			minIndex = i;
			min = arr[minIndex];
			
		}
	}
	int empty = 0;
	empty = minIndex;
	
	node = makeCopy(arr[minIndex]);
	free(arr[minIndex]->token);
	free(arr[minIndex]);
	arr[minIndex] = NULL;
	
	for (int i = 0; i < numItems; i ++) {
		if (arr[i] != NULL) {
			minIndex = i;
			break;
		}
	}
	min = arr[minIndex];
	for (int i = 0; i < numItems; i ++) {
		if (arr[i] != NULL && (arr[i]->freq < min->freq)) {
			minIndex = i;
			min = arr[minIndex];
		}
	}
	
	node1 = makeCopy(arr[minIndex]);
	free(arr[minIndex]->token);
	free(arr[minIndex]);
	arr[minIndex] = NULL;

	if (node != NULL && node1 != NULL) {
		struct huffmanTree *combined = combine(node, node1);
		combined->left = node;
		combined->right = node1;
		arr[empty] = combined;
		return;
	}
}

struct huffmanTree *createNode() {
	struct huffmanTree *new = malloc(sizeof(struct huffmanTree));
	new->token = NULL;
	new->freq = 0;
	new->left = NULL;
	new->right = NULL;
	return new;
}

static void mergeSort(struct item *counterItems, int lo, int hi) {
	if (lo >= hi) {
		return;
	}
	int mid = (lo + hi) / 2;
	mergeSort(counterItems, lo, mid);
	mergeSort(counterItems, mid + 1, hi);
	merge(counterItems, lo, mid, hi);
}

static void merge(struct item *counterItems, int lo, int mid, int hi) {
	struct item *temp = malloc((hi - lo + 1) * sizeof(struct item));
	int i = lo, j = mid + 1, k = 0;
	while (i <= mid && j <= hi) {
		if (counterItems[i].freq <= counterItems[j].freq) {
			temp[k] = counterItems[i];
			k ++;
			i ++;
		} else {
			temp[k] = counterItems[j];
			k ++;
			j ++;
		}
	}
	while (i <= mid) {
		temp[k] = counterItems[i];
		k++;
		i ++;
	}
	while (j <= hi) {
		temp[k] = counterItems[j];
		k++;
		j ++;
	}
	for (i = lo, k = 0; i <= hi; i ++, k ++) {
		counterItems[i] = temp[k];
	}
	
	free(temp);
}

static void freeCounterItems(struct item *counterItems, int numItems) {
	for (int i = 0; i < numItems; i ++) {
		free(counterItems[i].token);
	}
}

// Task 4
char *encode(struct huffmanTree *tree, char *inputFilename) {
	char token[MAX_TOKEN_LEN];
	int size = findHowManyTokens(tree);
	struct tokenInfo *encodingArr = malloc(sizeof(struct tokenInfo) * size);
	for (int i = 0; i < size; i ++) {
		encodingArr[i].token = NULL;
		encodingArr[i].encoding = NULL;
	}
	File f = FileOpenToRead(inputFilename);
	int strCatIndex = 0;
	int mallocSize = 0;
	char *finalStr = malloc(sizeof(char) * strCatIndex);
	// size of array that contains encoding details
	int encoSize = 0;
	while (FileReadToken(f, token)) {
		//	fetch index of token from encoding array, if not in then return -1
		int result = bstToken(encodingArr, token, &encoSize);
		if (result == -1) {
			//	Not in, have to insert
			//	traverse tree, fetch path in string, return string
			//	insert to encodingArr in order
			//	realloc final string output
			//	encode
			bool found = false;
			struct stack *s = malloc(sizeof(struct stack));
			s->size = 0;
			s->head = NULL;
			s = findPath(tree, token, s, &found);

			//	Encode into string
			char *encoding = malloc(sizeof(char) * (s->size + 1));
			int encodingIndex = 0;
			getEncodingStr(s->head, encoding, &encodingIndex);
			encoding[encodingIndex] = '\0';
			
			bstInsert(encodingArr, token, encoding, &encoSize);
			if (strCatIndex == 0) {
				finalStr = realloc(finalStr, (strCatIndex + strlen(encoding) + 1) * sizeof(char));
				mallocSize += (strCatIndex + strlen(encoding) + 1);
			} else {
				if (mallocSize < (strCatIndex + strlen(encoding) + 1)) {
					finalStr = realloc(finalStr, (mallocSize * 100) * sizeof(char));
					mallocSize *= 100;
				}
			}
			strCopy(encoding, finalStr, strCatIndex);
			strCatIndex += (strlen(encoding));

			freeStackList(s->head);
			free(s);
			free(encoding);;
			
		} else {
			// fetch from encodingArr
			if (mallocSize < (strCatIndex + strlen(encodingArr[result].encoding) + 1)) {
					finalStr = realloc(finalStr, (mallocSize * 100) * sizeof(char));
					mallocSize *= 100;
			}
			
			strCopy(encodingArr[result].encoding, finalStr, strCatIndex);
			strCatIndex += (strlen(encodingArr[result].encoding));
			// realloc final string output
			// encode right away
		}
	}
	freeEncodingArr(encodingArr, size);
	free(encodingArr);
	FileClose(f);
	return finalStr;
}

void bstInsert(struct tokenInfo *encodingArr, char *token, char *encoding, int *size) {
	int i = 0;
	if ((*size) == 0) {
			encodingArr[i].token = strdup(token);
			encodingArr[i].encoding = strdup(encoding);
			(*size) ++;
			return;
	}
	while (i < (*size)) {
		if (strcmp(encodingArr[i].token, token) == 0) {
			return;
		}
		if (strcmp(encodingArr[i].token, token) > 0) {
			
			struct tokenInfo temp = encodingArr[i] ;
			struct tokenInfo next = encodingArr[i + 1];
			(*size) ++;
			for (int j = i; j < ((*size)); j ++) {
				if (j == i) {
					encodingArr[j].token = strdup(token);
					encodingArr[j].encoding = strdup(encoding);
				
				} else {
						encodingArr[j] = temp;
					temp = next;
					if (j + 1 < *size) {
						next = encodingArr[j + 1];
					}
				}
			}
			
			return;
		}
		i ++;
	}
}

int bstToken(struct tokenInfo *encodingArr, char *token, int *size) {
	int lo = 0;
	int hi = (*size) - 1;
	int i = lo, j = hi;
	while (i <= j) {
		int mid = (i + j) / 2;
		
		if (strcmp(encodingArr[mid].token, token) == 0) {
			return mid;
		}
		if (strcmp(encodingArr[mid].token, token) < 0) {
			i = mid + 1;
		} else if (strcmp(encodingArr[mid].token, token) > 0) {
			j = mid - 1;
		}
	}
	return -1;
}


struct stack *findPath(struct huffmanTree *tree, char *token, struct stack *s, bool *found) { 
	if (tree == NULL) {
		return s;
	}
	if (tree->left == NULL && tree->right == NULL && (strcmp(tree->token, token) == 0)) {
		*found = true;
		return s;
	}
	
	s = insertList(s, 0);
	s = findPath(tree->left, token, s, found);
	if (*found == false) {
		s = deleteList(s);
	}

	// going right if havent found
	if (*found == false) {
		s = insertList(s, 1);

		s = findPath(tree->right, token, s, found);
		if (*found == false) {
			s = deleteList(s);
		}
	}
	return s;
}



static struct stack *insertList(struct stack *s, int num) {
	if (s->head == NULL) {
		struct list *newList = malloc(sizeof(struct list));
		newList->next = NULL;
		newList->num = num;
		s->head = newList;
		s->size ++;
		return s;
	}
	struct list *newList = malloc(sizeof(struct list));
	newList->next = s->head;
	newList->num = num;
	s->head = newList;
	s->size ++;
	return s;
}

static struct stack *deleteList (struct stack *s) {
	struct list *old = s->head;
	s->head = s->head->next;
	free(old);
	return s;
}

static void getEncodingStr(struct list *l, char *arr, int *index) {
	if (l == NULL) {
		return;
	}
	getEncodingStr(l->next, arr, index);
	if (l->num == 0) {
		arr[*index] = '0';
		(*index) ++;
	} else if (l->num == 1) {
		arr[*index] = '1';
		(*index) ++;
	}
}

void strCopy(char *source, char *destination, int index) {
	int i = 0;
	while (source[i] != '\0') {
		destination[index] = source[i];
		index ++;
		i ++;
	}
	destination[index] = '\0';
}

int findHowManyTokens(struct huffmanTree *tree) {
	if (tree == NULL) {
		return 0;
	}
	if (tree->left == NULL && tree->right == NULL) {
		return 1;
	}
	return findHowManyTokens(tree->left) + findHowManyTokens(tree->right);
}

void freeStackList(struct list *l) {
	if (l == NULL) {
		return;
	}
	freeStackList(l->next);
	free(l);
}

void freeEncodingArr(struct tokenInfo *encodingArr, int size) {
	for (int i = 0; i < size; i ++) {
		free(encodingArr[i].token);
		free(encodingArr[i].encoding);
	}
}