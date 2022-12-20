
# macros:
# compC = gcc -no-pie -m32 -g -Wall -c -o
# complC = gcc -no-pie -m32 -g -Wall -o
# complS = nasm -g -f elf -w+all -o


all: task2

# (target) : (dependencies)
task2 :  main.o start.o util.o
	ld -m elf_i386 start.o main.o util.o -o task2

main.o : main.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o

util.o : util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

start.o : start.s
	nasm -f elf32 start.s -o start.o


.PHONY : clean

clean:
	rm -f *.o task2