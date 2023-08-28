CC = gcc
FLAGS = -Werror -Wall

linkedlist: linkedlist.o linkedlist_lib.o
	$(CC) $(FLAGS) -o linkedlist linkedlist.o linkedlist_lib.o

linkedlist.o : linkedlist.c
	$(CC) $(FLAGS) -c linkedlist.c 

linkedlist_lib.o : linkedlist_lib.c
	$(CC) $(FLAGS) -c linkedlist_lib.c 

clean :
	rm -f *.o linkedlist