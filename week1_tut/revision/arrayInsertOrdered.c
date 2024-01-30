
#include <stdio.h>
#include <stdlib.h>

void insertOrdered(int *arr, int size, int value);

void printArray(int *arr, int size);

int main(void) {
	printf("Enter array size: ");
	int size = 0;
	if (scanf("%d", &size) != 1) {
		fprintf(stderr, "error: failed to read array size\n");
		exit(EXIT_FAILURE);
	} else if (size < 0) {
		fprintf(stderr, "error: invalid array size\n");
		exit(EXIT_FAILURE);
	}

	int *arr = malloc((size + 1) * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	if (size > 0) {
		printf("Enter array values (must be in ascending order): ");
	}
	for (int i = 0; i < size; i++) {
		if (scanf("%d", &arr[i]) != 1) {
			fprintf(stderr, "error: failed to read array value\n");
			exit(EXIT_FAILURE);
		} else if (i > 0 && arr[i] < arr[i - 1]) {
			fprintf(stderr, "error: array is not in ascending order\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Array: ");
	printArray(arr, size);

	printf("Enter value to insert: ");
	int value = 0;
	if (scanf("%d", &value) != 1) {
		fprintf(stderr, "error: failed to read value\n");
		exit(EXIT_FAILURE);
	}

	insertOrdered(arr, size, value);
	printf("Array after inserting %d: ", value);
	printArray(arr, size + 1);

	free(arr);
	return EXIT_SUCCESS;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task	

void insertOrdered(int *arr, int size, int value) {
	if (size == 0) {
		arr[0] = value;
		return;
	}
	// TODO
	for (int i = 0; i < size; i ++) {
		if (value < arr[i]) {	
			int temp;
			int temp1;
			for (int j = i; j < size + 1; j ++) {
				if (j == i) {
					temp = arr[j];	
					temp1 = arr[j + 1];
					arr[j] = value;
				} else {
					arr[j] = temp;
					temp = temp1;
					if (j < size - 1) {
						temp1 = arr[j + 1];
					}
				}
			}
			return;
		}
	}
	if (value > arr[size - 1]) {
		arr[size] = value;
	}
}

////////////////////////////////////////////////////////////////////////
// !!! DO NOT MODIFY THE CODE BELOW !!!

void printArray(int *arr, int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		if (i > 0) {
			printf(", ");
		}
		printf("%d", arr[i]);
	}
	printf("]\n");
}

