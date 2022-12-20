#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int iarray[] = {1,2,3};
    char carray[] = {'a','b','c'};
    int* iarrayPtr;
    char* carrayPtr;
    iarrayPtr = &iarray;
    carrayPtr = &carray;
    int* p;
    printf("%d, %d, %d \n",*iarrayPtr, *iarrayPtr+1, *iarrayPtr+2);
    printf("%c, %c, %c \n",*carrayPtr, *carrayPtr+1, *carrayPtr+2);
    printf("%p\n %p \n", p, iarrayPtr);
 // the + operator in this case moves to the beginning of the next element in the stack, 
 // if we created an array if 3 ints then the difference between the beginning of the array
 // and the array +1 will be 12 (3*int size)
}