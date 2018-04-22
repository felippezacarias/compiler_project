#include "lexico.h"

//Variável global do número de linhas
int linhaCodigo = 1;

//Preenchendo a tabela de palavras reservadas
char TAB_PR[][30]={"int","void","return","while","else","if"};

//preenchendo a tabela de sinais
char TAB_SN[][3]={"+","-","*","/","<","<=",">",">=","==","!=","=",";",",","(",")","[","]","{","}"};


token analisadorLexico(FILE *fp){
      
     
    int encontrouToken =0;
    int estadoAtual =0;
    int b=0;
    int resultado=0;
    int resultado2=0;
    char c;
    char literal[100];
    int indice =0;
    
    token tokenTeste;

    while(!encontrouToken){
        
        c=getc(fp);

        //reconhece letras
        if(isalpha(c) && (( estadoAtual == 0)||(estadoAtual == 1))){
            estadoAtual=1;
            tokenTeste.lexema[b++]=c;
        }
        //reconhece digitos                                                
        else if((isdigit(c) && (estadoAtual == 1))){
                estadoAtual=1;
                tokenTeste.lexema[b++]=c;
            }
        else if((isdigit(c)) && ((estadoAtual == 0) || (estadoAtual == 2))){
                estadoAtual=2;
                tokenTeste.lexema[b++]=c;
            }                     
        /*Aqui vou tratar comentário */                         
        else if(( c == '/') && (estadoAtual == 0) ){
                estadoAtual=5;
                tokenTeste.lexema[b++]=c;
            }             
        else if((c == '*') && (estadoAtual == 0)){//Aqui configura-se o caso do asterisco
                estadoAtual=3;               //se uma multiplição     
                tokenTeste.lexema[b++]=c;
            }          
        else if((c == '*') && (estadoAtual == 5)){//caso contrario ele é o início do
                estadoAtual=6;                  //comentário        
                b=0; 
            }         
        else if((c == '*') && ((estadoAtual == 6) || (estadoAtual == 7))){
                estadoAtual=7;
            }      
        else if(( c == '/') && (estadoAtual == 7) ){//chegou ao final do comentário
                estadoAtual=0;
            }
        else if( ((c == '<') || (c == '>') || (c == '=') || (c == '!') ) && (estadoAtual == 0)){
                estadoAtual=4;
                tokenTeste.lexema[b++]=c;
            }
        else if((c == '=') && (estadoAtual == 4)){
                estadoAtual=3;
                tokenTeste.lexema[b++]=c;
            }
        //Aqui vai tratar de todos os sinais da linguagem
        else if((estadoAtual == 0) && ((c == ';') || (c == ',') || (c == '{') || (c == '}') ||
                (c == '(') || (c == ')') || (c == '[') || (c == ']')  || (c == '+') || (c == '-') )){
                    estadoAtual=3;
                    tokenTeste.lexema[b++]=c;
            }
        //Aqui incrementa a linha do código      
        else if( ((estadoAtual ==0) || (estadoAtual ==6 )|| (estadoAtual == 7))&&(c == '\n')) linhaCodigo++;
        //Aqui trata o branco, não faz nada
        else if( ((estadoAtual == 0) || (estadoAtual == 6) ||(estadoAtual ==7))
                    &&((c == ' ') || (c == '\t')) ){}
         //Continuação do tratamento do comentário uma vez que ele vai receber qualquer caracter
         //imprimível;              
         else if((isprint(c)) && ((estadoAtual == 6) || (estadoAtual == 7))){
                estadoAtual=6;
            }
        //Aqui vai ser o último caso        
        else if((c == EOF) && ( estadoAtual == 0 )){
                printf("\nFIM DE ARQUIVO ENCONTRADO\n");
                exit(0);
                //estadoAtual = -1;
                //encontrouToken =1;
            }
        else{
             encontrouToken=1;
             tokenTeste.lexema[b]='\0';
             ungetc(c,fp);               
            }
    }//Fim while

    //switch que vai analisar o lexema a partir do estado final        
    switch (estadoAtual){
            
        case 0: printf("\n\nERRO CARACTER [ %c ] INVALIDO LINHA: %d\n\n",c,linhaCodigo);
                exit(0);
        break; 

        case 1: resultado = procurarPalavraReservada(tokenTeste.lexema);
                if(resultado != -1){
                    tokenTeste.tipo = PR;
                    tokenTeste.codigoPR = resultado;
                }
                else tokenTeste.tipo = ID;
        break;   

        case 2: tokenTeste.valorInt = atoi(tokenTeste.lexema);
                tokenTeste.tipo = CTI;
        break;

        case 3:resultado2 = procurarSinal(tokenTeste.lexema);
                tokenTeste.tipo = SN;
                tokenTeste.codigoSinal = resultado2; 
        break;   

        case 4: resultado2 = procurarSinal(tokenTeste.lexema);
                tokenTeste.tipo = SN;
                tokenTeste.codigoSinal = resultado2;
        break;

        case 5: resultado2 = procurarSinal(tokenTeste.lexema);
                tokenTeste.tipo = SN;
                tokenTeste.codigoSinal = resultado2;
        break;

        case 6: printf("\n\nERRO FECHAMENTO DE COMENTARIO ESPERADO LINHA: %d\n\n",linhaCodigo);
                exit(0);
        break;

        case 7: printf("\n\nERRO FECHAMENTO DE COMENTARIO ESPERADO LINHA: %d\n\n",linhaCodigo);
                exit(0);
        break;
            
        default: printf("\n\nERRO CARACTER ESPERADO LINHA: %d\n\n",linhaCodigo);
                exit(0);
        
    }//Fim switch

   return tokenTeste;

}//Fim analisador léxico



//#############################################################################################################

//função que compara o token encontrado com as palavras da tabela de palavras reservadas
int procurarPalavraReservada(char * palavra){

     int i;
     int resultado =-1;
     
     for(i=0;i<LIN_TAB_PR;i++){
                       if(!strcmp(palavra,TAB_PR[i])){ // ver se essa compara��o ta fazendo correto
                                 resultado=i;
                                 break;
                                 }
     }
 return resultado;                     

}

//função que compara o token encontrado com os sinais da tabela de sinais reservadas
int procurarSinal(char * palavra){

     int i;
     int resultado =-1;
     
     for(i=0;i<LIN_TAB_SN;i++){
                       if(!strcmp(palavra,TAB_SN[i])){
                              resultado=i;
                              break;
                              }
     }
 return resultado;                     

}