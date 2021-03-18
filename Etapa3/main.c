// Aluno: Gabriel Lando

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "y.tab.h"

extern char * yytext;
extern FILE * yyin;
extern int yylex();
extern int yyparse();
extern ASTREE_NODE * GetAST();

void initMe(void);
int isRunning(void);

int main(int argc, char ** argv) {
    int token = 0;
    FILE * out;
    fprintf(stderr, "Rodando main que nao eh do prof na etapa 3.\n\n");

    if (argc < 3) {
        printf("call: ./etapa3 input.txt output.txt\n");
        return 1;
    }
    if (!(yyin = fopen(argv[1], "r"))) {
        printf("Cannot open file %s... \n", argv[1]);
        return 1;
    }
    if (!(out = fopen(argv[2], "w+"))) {
        printf("Cannot open file %s\n", argv[2]);
        return 1;
    }

    initMe();
    yyparse();

    hashPrint();

    ASTREE_NODE * root = GetAST();
    UncompileAST(out, root);

    fclose(out);

    fprintf(stderr, "\nSuper! Compilation successful!\n");

    return 0;
}