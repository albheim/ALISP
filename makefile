CC = gcc
CFLAGS = -std=c99 -Wall

run: compile
	./a.out

compile: 
	$(CC) $(CFLAGS) parser.c mpc.c -ledit -lm

cleanup:
	rm -rf *.o a.out

