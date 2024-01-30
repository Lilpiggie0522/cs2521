
#include <stdio.h>
#include <stdlib.h>

void shift(int *arr, int size, int n);

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

	int *arr = malloc(size * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	if (size > 0) {
		printf("Enter array values: ");
	}
	for (int i = 0; i < size; i++) {
		if (scanf("%d", &arr[i]) != 1) {
			fprintf(stderr, "error: failed to read array value\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Array: ");
	printArray(arr, size);

	printf("Enter shift: ");
	int n = 0;
	if (scanf("%d", &n) != 1) {
		fprintf(stderr, "error: failed to read shift\n");
		exit(EXIT_FAILURE);
	} else if (n < 0) {
		fprintf(stderr, "error: invalid shift\n");
		exit(EXIT_FAILURE);
	}

	shift(arr, size, n);
	printf("Array after shifting %d time(s): ", n);
	printArray(arr, size);

	free(arr);
	return EXIT_SUCCESS;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

void shift(int *arr, int size, int n) {
	// TODO
	for (int i = 0; i < n; i ++) {
		int j;
		int temp = 0;
		int temp1 = 0;
		int last = 0;
		if (size > 0) {
			last = arr[size - 1];
		}
		for (j = 0; j < size; j ++) {
			
			if (j == 0) {
				temp = arr[j];
				temp1 = arr[j + 1];
			} else {
				arr[j] = temp;
				temp = temp1;
				if (j < size - 1) {
					temp1 = arr[j + 1];
				}
			}
			
		}
		if (size > 0) {
			arr[0] = last;
		}
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

