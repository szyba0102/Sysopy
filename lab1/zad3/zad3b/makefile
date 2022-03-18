CC = gcc
CFLAGS = -Wall -g
REPORT_FILE = raport3b.txt


static:
	$(CC) $(CFLAGS) -c library.c -o library.o
	ar rcs liblibrary.a library.o
	$(CC) $(CFLAGS) main.c -llibrary -L./ -o main -$O


shared:
	$(CC) $(CFLAGS) -fPIC -shared library.c -o liblibrary.so
	$(CC) $(CFLAGS) main.c -L. -Wl,-rpath=. -llibrary -o main -$O


dynamic:
	$(CC) $(CFLAGS) -fPIC -shared library.c -o liblibrary.so
	$(CC) $(CFLAGS) main.c -ldl -D DYNAMIC -o main -$O

test:
	./main $(shell cat args.txt)


test_O0:
	printf "static O0:\n" >> raport.txt
	make static O=O0
	make test
	make clean

	printf "shared O0:\n" >> raport.txt
	make static O=O0
	make test
	make clean

	printf "dynamic O0:\n" >> raport.txt
	make static O=O0
	make test
	make clean
test_O2:
	printf "static O2:\n" >> raport.txt
	make static O=O2
	make test
	make clean

	printf "shared O2:\n" >> raport.txt
	make shared O=O2
	make test
	make clean

	printf "dynamic O2:\n" >> raport.txt
	make dynamic O=O2
	make test
	make clean
test_Os:
	printf "static Os:\n" >> raport.txt
	make static O=Os
	make test
	make clean

	printf "shared Os:\n" >> raport.txt
	make shared O=Os
	make test
	make clean

	printf "dynamic Os:\n" >> raport.txt
	make dynamic O=Os
	make test
	make clean

test_all:
	make test_O0
	make test_O2
	make test_Os
	mv raport.txt $(REPORT_FILE)

clean:
	rm -f *.so *.o *.a
