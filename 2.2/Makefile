CC = gcc
FLAGS = -Werror -Wall

testSet : Set_Linkedlist.o testSet.o
	$(CC) $(FLAGS) -o testSet testSet.o Set_Linkedlist.o

testSet.o : testSet.c 
	$(CC) $(FLAGS) -c testSet.c

Set_Linkedlist.o : Set_Linkedlist.c
	$(CC) $(FLAGS) -c Set_Linkedlist.c