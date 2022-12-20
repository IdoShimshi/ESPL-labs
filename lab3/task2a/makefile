all: virus

virus: virus.o
	gcc -m32 -g -Wall -o virus virus.o

virus.o: virus.c
	gcc -g -Wall -m32 -c -o virus.o virus.c

.PHONY: clean
clean:
	rm -f *.o virus