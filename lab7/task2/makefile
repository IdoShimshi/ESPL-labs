mypipeline: mypipeline.o
	gcc -m32 -Wall -g -o mypipeline mypipeline.o 

mypipeline.o: mypipeline.c
	gcc -g -Wall -m32 -c -o mypipeline.o mypipeline.c

.PHONY: clean
clean:
	rm -f *.o mypipeline
