all: arr-mem

arr-mem: arr-mem.o
	gcc -m32 -g -Wall -o arr-mem arr-mem.o

arr-mem.o: arr-mem.c
	gcc -g -Wall -m32 -c -o arr-mem.o arr-mem.c

.PHONY: clean
clean:
	rm -f *.o arr-mem