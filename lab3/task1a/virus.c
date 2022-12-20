
#include <stdio.h>
#include <stdlib.h>

typedef struct virus {
unsigned short SigSize;
char virusName[16];
unsigned char* sig;
} virus;

virus* readVirus(FILE* f){
    virus* ret = malloc(sizeof(virus));
    ret->SigSize = 0;
    fread(&(ret->SigSize),1, 18, f);
    ret->sig = malloc(ret->SigSize);
    fread(ret->sig,1, ret->SigSize, f);
    return ret;
}

void printVirus(virus* virus , FILE* output){
    fprintf(output,"Virus name: %s\n", virus->virusName);
    fprintf(output,"Virus size: %d\n", virus->SigSize);
    fprintf(output,"signature:\n");
    int count = 0;
    for (int i = 0; i < virus->SigSize; i++){
        if (count == 20)
        {
            fprintf(output,"\n");
            count = 0;
        }
        fprintf(output,"%02X ", virus->sig[i]);
        count++;
    }
    fprintf(output,"\n");
}

int main(int argc, char **argv){
    if (argc != 2)
        exit(1);
    FILE* input = fopen(argv[1],"r");
    int *ignore = malloc(4);
    fread(ignore,4, 1,input);
    free(ignore);
    FILE* output = fopen("output_virus","w");
    virus* v;
    while (1)
    {
        v = readVirus(input);
        if (v->SigSize == 0)
        {
            free(v->sig);
            free(v);
            break;
        }
        printVirus(v, output);
        fprintf(output,"\n");
        free(v->sig);
        free(v);
    }
}