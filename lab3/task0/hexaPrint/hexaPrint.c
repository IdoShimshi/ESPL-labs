#include <stdio.h>
#include <stdlib.h>


void PrintHex(char* buffer , int length){
    for (int i = 0; i < length; i++)
        printf("%X ", buffer[i]);
    printf("\n");
}

int main(int argc, char **argv){
    if (argc == 2)
    {
        FILE *fp = fopen(argv[1], "r");
        char buf[100];
        int idk = fread(buf,sizeof(char), 100, fp);
        PrintHex(buf,idk);
        fclose(fp);
    }
}
