defaults:
	touch tomb/decrypted.txt
	gcc -o build/main.o src/*.c main.c -Wall -Werror -Wextra -g -lm
	./build/main.o
