defaults:
	gcc -o build/main.o *.c -Wall -Wextra -g -lm
	./build/main.o
