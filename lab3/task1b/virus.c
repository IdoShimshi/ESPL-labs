
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
// ====================================<VIRUS>====================================
typedef struct virus {
unsigned short SigSize;
char virusName[16];
unsigned char* sig;
} virus;

virus* readVirus(FILE* f){
    virus* ret = malloc(sizeof(virus));
    if (fread(&(ret->SigSize),1, 18, f) != 18){
        free(ret);
        return NULL;
    }
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
// ====================================<LINK>====================================
typedef struct link {
struct link *nextVirus;
virus *vir;
} link;

void list_print(link* virus_list, FILE* output){
    link* curVirLink = virus_list;
    while (curVirLink != NULL)
    {
        printVirus(curVirLink->vir, output);
        fprintf(output,"\n");
        curVirLink = curVirLink->nextVirus;
    }
}

link* list_append(link* virus_list, virus* data){
    link* newLink = malloc(sizeof(link));
    newLink->nextVirus = virus_list;
    newLink->vir = data;
    return newLink;
}

void list_free(link *virus_list){
    link* curLink = virus_list;
    link* nextLink;
    while (curLink != NULL)
    {
        nextLink = curLink->nextVirus;
        free(curLink->vir->sig);
        free(curLink->vir);
        free(curLink);
        curLink = nextLink;
    }
}

link* loadSig(){
    char fileName[100];
    char *p;
    fgets(fileName,sizeof(fileName),stdin);
    p = strchr(fileName, '\n');
    *p = '\0';

    FILE* input = fopen(fileName,"r");
    int *ignore = malloc(4);
    fread(ignore,4, 1,input);
    free(ignore);
        
    virus* v = readVirus(input);
    link* ret = NULL;
    while (v != NULL)
    {
        ret = list_append(ret, v);
        v = readVirus(input);
    }
    return ret;
}

void detect(){
    printf("Not implemented\n");
}

void fix(){
    printf("Not implemented\n");
}

void quit(char c){
    exit(0);
}

int main(int argc, char **argv){
    char option[5];
    int choice;
    link* viruses = NULL;
    while (1)
    {
        printf("1) Load signatures\n2) Print signatures\n3) Detect viruses\n4) Fix file\n5) Quit\n");
        printf("option: ");
        fgets(option,5,stdin);
        sscanf(option,"%d", &choice);
        if (choice == 1){
            list_free(viruses);
            viruses = loadSig();
        }
        else if (choice == 2)
            list_print(viruses, stdout);
        else if (choice == 3)
            detect();
        else if (choice == 4)
            fix();
        else if (choice == 5){
            list_free(viruses);
            exit(0);
        }
        else
            printf("Not within bounds\n");
    }
}