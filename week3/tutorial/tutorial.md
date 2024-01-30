2.
Bubble sort:
    sorted: n
    reverse sorted: ((n-1)+(n-2)+(n-3)+...)*n n^2
    sorted but first last swapped: n^2

Insertion sort:
    sorted: n
    reverse sorted: (1 + 2 + 3 + ...+ (n-1)) * n
    sorted but first last swapped: 1 + 2*(n-2)

4.
                 ij
{ 4, 3, 1, 2, 5, 6, 9, 8, 9, 7 }      index = 4          

        ij
b. { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }  index = 0

                                ij
c. { 0, 8, 7, 6, 5, 4, 3, 2, 1, 9 } index = 9


revision questions: 
    2.
    a. Selection: 4 + 3 + 2 + 1
    4 3 6 8 2
    3 4 6 2 8 4c
    3 4 2 6 8 7c
    3 2 4 6 8 9c
    2 3 4 6 8 10c       
    
b. Bubble: 10