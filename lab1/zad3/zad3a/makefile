CC = gcc
CFLAGS = -Wall  -g
REPORT_FILE = raport3a.txt

static:
	$(CC) $(CFLAGS) -c library.c -o library.o
	ar rcs liblibrary.a library.o
	$(CC) $(CFLAGS) main.c -llibrary -L./ -o main


shared:
	$(CC) $(CFLAGS) -fPIC -shared library.c -o liblibrary.so
	$(CC) $(CFLAGS) main.c -L. -Wl,-rpath=. -llibrary -o main


dynamic:
	$(CC) $(CFLAGS) -fPIC -shared library.c -o liblibrary.so
	$(CC) $(CFLAGS) main.c -ldl -D DYNAMIC -o main

test:
	./main $(shell cat args.txt)

test_all:
	printf "static:\n" >> raport.txt
	make static
	make test
	make clean
	printf "shared:\n" >> raport.txt
	make shared
	make test
	make clean
	printf "dynamic:\n" >> raport.txt
	make dynamic
	make test
	make clean
	mv raport.txt $(REPORT_FILE)

clean:
	rm -f *.so *.o *.a
