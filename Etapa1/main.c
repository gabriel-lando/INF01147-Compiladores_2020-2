// Aluno: Gabriel Lando

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

//lex.yy.h
int yylex();
extern char * yytext;
extern FILE * yyin;

int isRunning(void);

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
    while (isRunning()) {
        token = yylex();

        if (!isRunning())
            break;
            
        switch(token) {
            case KW_CHAR: printf("KW_CHAR (%s)\n", yytext); break;
            case KW_INT: printf("KW_INT (%s)\n", yytext); break;
            case KW_BOOL: printf("KW_BOOL (%s)\n", yytext); break;
            case KW_POINTER: printf("KW_POINTER (%s)\n", yytext); break;

            case KW_IF: printf("KW_IF (%s)\n", yytext); break;
            case KW_THEN: printf("KW_THEN (%s)\n", yytext); break;
            case KW_ELSE: printf("KW_ELSE (%s)\n", yytext); break;
            case KW_WHILE: printf("KW_WHILE (%s)\n", yytext); break;
            case KW_READ: printf("KW_READ (%s)\n", yytext); break;
            case KW_PRINT: printf("KW_PRINT (%s)\n", yytext); break;
            case KW_RETURN: printf("KW_RETURN (%s)\n", yytext); break;

            case OPERATOR_LE: printf("OPERATOR_LE (%s)\n", yytext); break;
            case OPERATOR_GE: printf("OPERATOR_GE (%s)\n", yytext); break;
            case OPERATOR_EQ: printf("OPERATOR_EQ (%s)\n", yytext); break;
            case OPERATOR_DIF: printf("OPERATOR_DIF (%s)\n", yytext); break;
            case LEFT_ASSIGN: printf("LEFT_ASSIGN (%s)\n", yytext); break;
            case RIGHT_ASSIGN: printf("RIGHT_ASSIGN (%s)\n", yytext); break;
            case TK_IDENTIFIER: printf("TK_IDENTIFIER (%s)\n", yytext);break;

            case LIT_INTEGER: printf("LIT_INTEGER (%s)\n", yytext); break;
            case LIT_TRUE: printf("LIT_TRUE (%s)\n", yytext); break;
            case LIT_FALSE: printf("LIT_FALSE (%s)\n", yytext); break;
            case LIT_CHAR: printf("LIT_CHAR (%s)\n", yytext); break;
            case LIT_STRING: printf("LIT_STRING (%s)\n", yytext); break;

            case TOKEN_ERROR: printf("TOKEN_ERROR (%s)\n", yytext); break;

            default: printf("Outro: %c\n", yytext[0]); break;
        }

        ++i;
    }
    
    hashPrint();
}