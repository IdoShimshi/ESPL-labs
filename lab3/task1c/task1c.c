
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
    if (input == NULL){
        printf("file not found\n");
        return NULL;
    }
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
    fclose(input);
    return ret;
}

void detect_virus(unsigned char *buffer, unsigned int size, link *virus_list){
    link* curLink = virus_list;
    while (curLink != NULL)
    {
        for (int i = 0; i < size - curLink->vir->SigSize; i++)
        {
            if (memcmp(buffer+i,curLink->vir->sig, curLink->vir->SigSize)== 0){
                printf("VIRUS DETECTED!\n");
                printf("Starting location in file: %d\n", i);
                printf("Virus name: %s\n", curLink->vir->virusName);
                printf("Virus signature size: %d\n", curLink->vir->SigSize);
            }
        }
        curLink = curLink->nextVirus;
    }
}

void fix(){
    printf("Not implemented\n");
}

int main(int argc, char **argv){
    char option[5];
    unsigned char* buffer = NULL;
    FILE* input = NULL;
    int size;
    if (argc == 2){
        buffer = malloc(10000);
        input = fopen(argv[1], "r");
        size = fread(buffer,1,10000, input);
        fclose(input);
    }
    int choice;
    link* viruses = NULL;
    while (1)
    {
        printf("\n1) Load signatures\n2) Print signatures\n3) Detect viruses\n4) Fix file\n5) Quit\n");
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
            detect_virus(buffer, size, viruses);
        else if (choice == 4)
            fix();
        else if (choice == 5){
            free(buffer);
            list_free(viruses);
            exit(0);
        }
        else
            printf("Not within bounds\n");
    }
}