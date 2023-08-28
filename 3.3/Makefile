CC = gcc
FLAGS = -Werror -Wall

Tree : BSTree.o BSTree_Main.o
	$(CC) $(FLAGS) -o Tree BSTree.o BSTree_Main.o

BSTree_Main.o : BSTree_Main.c 
	$(CC) $(FLAGS) -c BSTree_Main.c

BSTree.o : BSTree.c
	$(CC) $(FLAGS) -c BSTree.c