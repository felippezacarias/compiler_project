#include "lexico.h"

//Variável global do número de linhas
int linhaCodigo = 1;

typedef enum {INT,VOID,RETURN,WHILE,ELSE,IF} palavraReservada;
//Preenchendo a tabela de palavras reservadas
char TAB_PR[][30]={"int","void","return","while","else","if"};

//preenchendo a tabela de sinais
char TAB_SN[][3]={"+","-","*","/","<","<=",">",">=","==","!=","=",";",",","(",")","[","]","{","}"};



//Fazer o automato para poder implementar a transição de estados.