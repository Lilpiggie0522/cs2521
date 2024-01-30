all: selection_sort selection_sort2 bubble_sort2 insertion_sort merge_sort mergeSort quickSort quick_sort bubble_sort radixSort

selection_sort: selection_sort.c
	clang -o selection_sort selection_sort.c -g -Werror -Wall

selection_sort2: selection_sort2.c
	clang -o selection_sort2 selection_sort2.c -g -Werror -Wall

bubble_sort2: bubble_sort2.c
	clang -o bubble_sort2 bubble_sort2.c -g -Werror -Wall

bubble_sort: bubble_sort.c
	clang -o bubble_sort bubble_sort.c -g -Werror -Wall

insertion_sort: insertion_sort.c
	clang -o insertion_sort insertion_sort.c -g -Werror -Wall

merge_sort: merge_sort.c
	clang -o merge_sort merge_sort.c -g -Werror -Wall

mergeSort: mergeSort.c
	clang -o mergeSort mergeSort.c -g -Werror -Wall

quickSort: quickSort.c
	clang -o quickSort quickSort.c -g -Werror -Wall

quick_sort: quick_sort.c
	clang -o quick_sort quick_sort.c -g -Werror -Wall


radixSort: radixSort.c
	# clang -o radixSort radixSort.c -g -Werror -Wall -fsanitize=address
	clang -o radixSort radixSort.c -g -Werror -Wall -fsanitize=memory

clean : 
	rm -f *.o selection_sort selection_sort2 bubble_sort2 insertion_sort2 quickSort quick_sort