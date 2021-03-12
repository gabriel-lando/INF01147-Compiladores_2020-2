// Aluno: Gabriel Lando

#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "hash.h"

//lex.yy.h
int yylex();
extern char * yytext;
extern FILE * yyin;

int isRunning(void);
int getLineNumber(void);
void initMe(void);

int main(int argc, char ** argv) {
    FILE * gold = 0;
    int token = 0;
    int answar = 0;
    int nota = 0;
    int i = 1;
    fprintf(stderr, "Rodando main que nao eh do prof. \n");

    if (argc < 2) {
        printf("call: ./etapa1 input.txt\n");
        exit(1);
    }
    if (0 == (yyin = fopen(argv[1], "r"))) {
        printf("Cannot open file %s... \n", argv[1]);
        exit(1);
    }

    initMe();

    yyparse();

    hashPrint();
}