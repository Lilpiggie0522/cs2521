CC = gcc
FLAGS = -Werror -Wall

Tree : BSTree_Main.o BSTree.o
	$(CC) $(FLAGS) -o Tree BSTree_Main.o BSTree.o

BSTree_Main.o : BSTree_Main.c 
	$(CC) $(FLAGS) -c BSTree_Main.c

BSTree.o : BSTree.c
	$(CC) $(FLAGS) -c BSTree.c