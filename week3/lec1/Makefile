all : queue_main set_main

brackets : brackets.c
	clang -g -Wall -Werror -o brackets brackets.c Stack.c -fsanitize=address

queue_main : queue_main.c 
	clang -g -Wall -Werror -o queue_main queue_main.c Queue.c


set_main : set_main.c 
	clang -g -Wall -Werror -o set_main set_main.c Set.c

clean:
	rm -rf queue_main set_main