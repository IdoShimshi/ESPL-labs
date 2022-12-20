mypipe : mypipe.o
	gcc -m32 -g -Wall -o mypipe mypipe.o

mypipe.o : mypipe.c
	gcc -m32 -g -Wall -o mypipe.o -c mypipe.c

.PHONY : clean
clean : 
	rm -f *.o mypipe