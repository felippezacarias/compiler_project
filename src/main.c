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
        case PR: puts("\nPalavra Reservada: ");
                puts(token1.lexema);
                puts("\nCódigoPR: ");
                printf(" %d\n",token1.codigoPR);
        break;         
        case ID: puts("\nIdentificador: ");
                puts(token1.lexema);
        break;         
        case SN: puts("\nSinal: ");
                puts(token1.lexema);
                puts("\nCódigoSN: ");
                printf(" %d\n",token1.codigoSinal);
        break;
        case CTI: puts("\nInteiro: ");
                puts(token1.lexema);
                puts("\nValor Inteiro: ");
                printf(" %d\n",token1.valorInt);
        break;
      }
    }

    fclose(fpin);
    fclose(fpout);
  
  return 0;
}
