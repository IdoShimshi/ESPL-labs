

# macros:
compC = gcc -no-pie -m32 -g -Wall -c -o
complC = gcc -no-pie -m32 -g -Wall -o
complS = nasm -g -f elf -w+all -o

.PHONY : clean

all: start

start :  start.o util.o
	ld -m elf_i386 start.o util.o -o start

util.o : util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

start.o : start.s
	nasm -f elf32 start.s -o start.o		
clean:
	rm -f *.o main
