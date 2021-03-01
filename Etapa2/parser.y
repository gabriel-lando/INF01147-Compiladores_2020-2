%{
// Aluno: Gabriel Lando
#include <stdio.h>
#include <stdlib.h>

#define SYMBOL_LIT_INT              1
#define SYMBOL_LIT_CHAR             2
#define SYMBOL_LIT_BOOL             3
#define SYMBOL_LIT_TRUE             4
#define SYMBOL_LIT_FALSE            5
#define SYMBOL_LIT_STRING           6
#define SYMBOL_IDENTIFIER           7

%}

%token KW_CHAR
%token KW_INT
%token KW_BOOL
%token KW_POINTER

%token KW_BYTE
%token KW_LONG
%token KW_FLOAT

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token LEFT_ASSIGN
%token RIGHT_ASSIGN

%token TK_IDENTIFIER

%token LIT_INTEGER
%token LIT_TRUE
%token LIT_FALSE
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '|' '&'
%left '<' '>'
%left OPERATOR_GE OPERATOR_LE
%left OPERATOR_EQ OPERATOR_DIF
%left LEFT_ASSIGN RIGHT_ASSIGN
%left '+' '-'
%left '*' '/'

%%

programa: programa dec
    |
    ;

dec: vardec
    | fundec
    | vectdec
    ;

vardec: type TK_IDENTIFIER ':' literal ';'
    ;

type: KW_INT
    | KW_BOOL
    | KW_POINTER
    ;

literal: LIT_INTEGER
    | LIT_TRUE
    | LIT_FALSE
    | LIT_CHAR
    | LIT_STRING
    ;

fundec: type TK_IDENTIFIER '(' param_list ')' cmd
    ;

vectdec: type TK_IDENTIFIER '[' LIT_INTEGER ']' vect_attr ';'
    ;

vect_attr: ':' vect_list
    |
    ;

vect_list: literal vect_list
    |
    ;

param_list: param other_params
    |
    ;

other_params: ',' param other_params
    |
    ;

param: type TK_IDENTIFIER
    ;

cmd: TK_IDENTIFIER ':' exp
    | TK_IDENTIFIER '[' exp ']' ':' exp
    | KW_READ TK_IDENTIFIER
    | KW_PRINT print_args
    | KW_RETURN exp
    | KW_IF '(' exp ')' KW_THEN cmd with_else
    | KW_WHILE '(' exp ')' cmd
    | block
    ;

with_else: KW_ELSE cmd
    |
    ;

print_args: exp print_args_rest
    ;

print_args_rest: print_args_sep exp print_args_rest
    |
    ;

print_args_sep: ','
    |
    ;

exp: exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | exp '<' exp
    | exp '>' exp
    | exp '.' exp
    | exp 'v' exp
    | exp OPERATOR_LE exp
    | exp OPERATOR_GE exp
    | exp OPERATOR_EQ exp
    | exp OPERATOR_DIF exp
    | exp LEFT_ASSIGN exp
    | exp RIGHT_ASSIGN exp
    | '~' exp
    | node
    | '(' exp ')'
    ;

node: TK_IDENTIFIER vect
    | literal
    | TK_IDENTIFIER '(' func_args ')'
    ;

vect: '[' exp ']'
    |
    ;

func_args: exp func_args_rest
    |
    ;

func_args_rest: ',' exp func_args_rest
    |
    ;

block: '{' lcmd '}'
    ;

lcmd: cmd ';' lcmd
    | cmd
    |
    ;

%%

int yyerror (char *msg)
{
	printf("Syntax error: %s - on line: %d.\n", msg, getLineNumber());
	exit(3);
}
