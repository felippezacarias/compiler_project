/* Projeto Compilador */

#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#define LIN_TAB_SN 6
#define LIN_TAB_PR 19



//Variável global do numero de linhas
int linhaCodigo;

//Criando a tabela com as palavras reservadas da linguagem
char TAB_PR[LIN_TAB_SN][30];

//criando a enumeração das palavras reservadas para servir como Id
typedef enum {INT,VOID,RETURN,WHILE,ELSE,IF} palavraReservada;



//criando a tabela dos sinais reservados e em baixo sua respectiva enumeração
char TAB_SN[LIN_TAB_PR][3];//={"+","-","*","/","<","<=",">",">=","==","!=","=",";",",","(",")","[","]","{","}"};


typedef enum{SOMA,SUBTRACAO,ASTERISCO,DIVISAO,MENORQ,MENORQIGUAL,MAIORQ,MAIORQIGUAL,IGUALIGUAL,NOTIGUAL,IGUAL,PONTOVIRGULA,
	         VIRGULA,ABREPARENTESES,FECHAPARENTESES,ABRECOLCHETES,FECHACOLCHETES,ABRECHAVES,FECHACHAVES} sinalReservado;

//Enumeração de categoria
//PR = palavra reservada
//ID = identificador
//CTI = valor inteiro
//SN = sinal
typedef enum {PR,ID,CTI,SN} categoria;


//Tipo Estruturado do token

typedef struct{
               char lexema[31];
               categoria tipo;
               union{
                      palavraReservada codigoPR;
                      sinalReservado codigoSinal;
                      int valorInt;
                    };
}token;


//funcões
token analisadorLexico(FILE *fp);

int procurarPalavraReservada(char * palavra);
int procurarSinal(char * palavra);






