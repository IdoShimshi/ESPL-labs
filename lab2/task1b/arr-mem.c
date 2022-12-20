#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int iarray[3];
    float farray[3];
    double darray[3];
    char carray[3];
    printf("- &iarray:   %p\n", &iarray);
    printf("- &iarray+1: %p\n", &iarray+1);
    printf("- &farray:   %p\n", &farray);
    printf("- &farray+1: %p\n", &farray+1);
    printf("- &darray:   %p\n", &darray);
    printf("- &darray+1: %p\n", &darray+1);
    printf("- &carray:   %p\n", &carray);
    printf("- &carray+1: %p\n", &carray+1);
 // the + operator in this case moves to the beginning of the next element in the stack, 
 // if we created an array if 3 ints then the difference between the beginning of the array
 // and the array +1 will be 12 (3*int size)
}