#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

int main(int argc, char *argv[])
{
    FILE *fp;
        
    fp = fopen("teste.txt", "r");
    
    if(fp == NULL) exit(0);
    
    fclose(fp);
  
  return 0;
}
