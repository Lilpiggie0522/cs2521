CC=gcc
FLAGS=-Wall -Werror

run : main.o library.o funAPP.o
	$(CC) -o run main.o library.o funAPP.o

main.o : main.c library.h
	$(CC) $(FLAGS) -c main.c

library.o : library.c library.h
	$(CC) $(FLAGS) -c library.c

funAPP.o : funAPP.c library.h
	$(CC) $(FLAGS) -c funAPP.c

