#include <stdio.h>

int main(int argc, char **argv) {
    int CAPDIFF='a'-'A';
    char c;
    while ((c=fgetc(stdin)) != EOF){
        if (c>= 97 && c<=122)
            fputc(c-CAPDIFF, stdout);
        else
            fputc(c,stdout);
    }
}