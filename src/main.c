#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

int main(int argc, char *argv[])
{
    FILE *fpin, *fpout;
    token token1;

    if(argc < 3){
      printf("Número de arqumentos passados [%d] deve ser igual a 2.\n",argc);
      exit(0);
    }
        
    fpin = fopen(argv[1], "r");
    fpout = fopen(argv[2], "w");

    if(fpin == NULL){
      printf("Não foi possível abrir o arquivo de entrada %s.\n",argv[1]);
      exit(0);
    } 

    if(fpout == NULL){
      printf("Não foi possível abrir o arquivo de saída %s.\n",argv[2]);
      exit(0);
    } 

    while(1){
      token1 = analisadorLexico(fpin);
             
      switch(token1.tipo){
        case PR: fprintf(fpout, "(%d,KEY,\"%s\")\n",linhaCodigo,token1.lexema);
        break;         

        case ID: fprintf(fpout, "(%d,ID,\"%s\")\n",linhaCodigo,token1.lexema);
        break;         

        case SN: fprintf(fpout, "(%d,SN,\"%s\")\n",linhaCodigo,token1.lexema);
        break;

        case CTI: fprintf(fpout, "(%d,CTI,\"%s\")\n",linhaCodigo,token1.lexema);
        break;
      }
    }

    fclose(fpin);
    fclose(fpout);
  
  return 0;
}
