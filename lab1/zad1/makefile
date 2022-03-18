CC = gcc
CFLAGS=-c -Wall

static:
	$(CC) $(CFLAGS) library.c
	ar rcs liblibrary.a library.o

shared:
	$(CC) $(CFLAGS) -fPIC library.c
	$(CC) -shared -fPIC -o library.so library.o

clean:
	rm -f *.so *.o *.a
