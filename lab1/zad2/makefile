CC = gcc
CFLAGS=-c -Wall

static:
	$(CC) $(CFLAGS) library.c
	ar rcs liblibrary.a library.o
	$(CC) $(CFLAGS) main.c
	$(CC) library.o main.o -o main

test:
	./main $(shell cat args.txt)

clean:
	rm -f *.so *.o *.a
