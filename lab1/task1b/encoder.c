#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int debug = 0;
    int CAPDIFF='a'-'A';
    for (int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i],"-D")==0){
            debug = 1;
        }
    }

    char c;
    char new_c;

 
    while ((c=fgetc(stdin)) != EOF){
        if (c>= 'a' && c<='z')
            new_c = c-CAPDIFF;
        else
            new_c = c;
        if (c != '\n' && debug)
            fprintf(stderr,"%x %x\n",c, new_c);
        fputc(new_c,stdout);
    }
}