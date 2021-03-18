// Aluno: Gabriel Lando

#ifndef __ASTREE__
#define __ASTREE__

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_MULT 4
#define AST_DIV 5
#define AST_LESS 6
#define AST_GREATER 7
#define AST_LE 8
#define AST_GE 9
#define AST_EQ 10
#define AST_DIF 11
#define AST_OR 12
#define AST_AND 13
#define AST_NOT 14
#define AST_IFT 15
#define AST_IFTE 16
#define AST_WHILE 17
#define AST_PRINT 18
#define AST_READ 19
#define AST_RETURN 20
#define AST_LCMD 21
#define AST_DECFUNC 22
#define AST_VARDEC 23
#define AST_ASSIGN 24
#define AST_ASSIGNARRAY 25
#define AST_ARRAY 26
#define AST_BLOCK 27
#define AST_PARENTH 28
#define AST_DECFUNC_VOID 29
#define AST_VETDEC 30
#define AST_DEC 31
#define AST_DEC_PARAM 32
#define AST_DEC_PARAM2 33
#define AST_PRINT_PARAM 34
#define AST_INT 35
#define AST_BOOL 36
#define AST_POINTER 37
#define AST_CHAR 38
#define AST_ARRAY_INIT 39
#define AST_ARRAY_INIT2 40
#define AST_FUNCCALL 41
#define AST_FUNC_PARAM 42
#define AST_FUNC_PARAM2 43
#define AST_VECSIZE 44
#define AST_DOLLAR 45
#define AST_HASH 46

typedef struct astree_node {
    int type;
    HASH_NODE * symbol;
    struct astree_node * sons[MAX_SONS];
}
ASTREE_NODE;

ASTREE_NODE * AstreeCreate(int type, HASH_NODE * symbol, ASTREE_NODE * son0, ASTREE_NODE * son1, ASTREE_NODE * son2, ASTREE_NODE * son3);
void AstreePrint(int level, ASTREE_NODE * node);
void UncompileAST(FILE * out, ASTREE_NODE * root);

#endif