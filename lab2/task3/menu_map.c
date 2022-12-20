#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
char censor(char c) {
  if(c == '!')
    return '.';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));

  for (int i = 0; i < array_length; i++)
  {
    mapped_array[i] = (*f)(array[i]);
  }
  return mapped_array;
}

char my_get(char c){
  return fgetc(stdin);
}

char cprt(char c){
  if (c >= 0x20 && c <= 0x7E)
    printf("%c\n",c);
  else
    printf(".\n");
  return c;
}

char encrypt(char c){
  if (c >= 0x20 && c <= 0x7E)
    return c+3;
  else
    return c;
}

char decrypt(char c){
  if (c >= 0x20 && c <= 0x7E)
    return c-3;
  else
    return c;
}

char xprt(char c){
  printf("%X\n",c);
  return c;
}

char quit(char c){
  if (c == 'q')
    exit(0);
  else
    return c;
}
 
struct fun_desc {
char *name;
char (*fun)(char);
};

int main(int argc, char **argv){
  char carray[5];
  *carray = '\0';
  char* carray_p = carray;

  struct fun_desc menu[] = { { "Get string", my_get }, { "Print string", cprt }, { "Encrypt", encrypt }, { "Censor", censor },
                             { "Decrypt", decrypt }, { "Print hex", xprt }, { "Quit", quit }, { NULL, NULL } };

  int menu_size = (sizeof(menu)/sizeof(struct fun_desc))-1;
  char option[5];
  int choice;
  
  while (1)
  {
    for (int i = 0; i < menu_size; i++)
        printf("%d)  %s\n",i, menu[i].name);

      printf("option: ");
      fgets(option,5,stdin);
      sscanf(option,"%d", &choice);

      if (choice >= 0 && choice <= menu_size)
      {
        printf("Within bounds\n");
        carray_p = map(carray_p, 5, menu[choice].fun);
      }
      else{
        printf("Not within bounds\n");
        exit(0);
      }
  }
}
