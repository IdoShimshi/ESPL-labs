#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int debug = 0;
    int CAPDIFF='a'-'A';
    int enc_direction = 1;
    int enc_pos = -1;
    int move_cycle;
    for (int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i],"-D")==0)
            debug = 1;
        if(strncmp(argv[i], "-e", 2) * strncmp(argv[i], "+e", 2) == 0){
            enc_pos = i;
            move_cycle = strlen(argv[enc_pos])-2;
            if (argv[i][0]=='-')
                enc_direction = -1;
        }
    }

    char c;
    char new_c;
    int count = 0;
    int move_by;
    
 
    while ((c=fgetc(stdin)) != EOF){
        if (c != '\n'){
            if (enc_pos >= 0){
                move_by = argv[enc_pos][2+(count % move_cycle)] - '0';
                new_c = c + (enc_direction * move_by);
                count++;
            }
            else if (c>= 'a' && c<='z')
            new_c = c-CAPDIFF;
            else
            new_c = c;

            if (debug)
            fprintf(stderr,"%x %x\n",c, new_c);
        }
        else{
            count =0;
            new_c = c;
        }
        fputc(new_c,stdout);
    }
}