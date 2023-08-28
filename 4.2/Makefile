CC = gcc
FLAGS = -Werror -Wall

tree : BSTree.o BSTree_Main.o
	$(CC) $(FLAGS) -o tree BSTree.o BSTree_Main.o

BSTree_Main.o : BSTree_Main.c 
	$(CC) $(FLAGS) -c BSTree_Main.c

BSTree.o : BSTree.c
	$(CC) $(FLAGS) -c BSTree.c