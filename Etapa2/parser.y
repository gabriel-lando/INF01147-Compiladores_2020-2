%{

	#include <stdio.h>
	#include <stdlib.h>
	#include "hash.h"

	int yyerror (char *msg);
	int yylex(void);
	int getLineNumber(void);

%}

%token KW_INT
%token KW_CHAR
%token KW_BOOL
%token KW_POINTER

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
%token LIT_CHAR
%token LIT_STRING
%token LIT_TRUE
%token LIT_FALSE

%token TOKEN_ERROR

%left '|' '&'
%left '<' '>'
%left OPERATOR_GE OPERATOR_LE
%left OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'
%left '~'
%left '#'
%left '$'

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
    | KW_CHAR
    | KW_BOOL
    | KW_POINTER
    ;

literal: LIT_INTEGER
    | LIT_CHAR
    | LIT_TRUE
    | LIT_FALSE
    ;

fundec: type TK_IDENTIFIER '(' param_list ')' block ';'
    ;

vectdec: type '[' LIT_INTEGER ']' TK_IDENTIFIER vect_attr ';'
    ;

vect_attr: ':' literal vect_list
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

block: '{' lcmd '}'
    ;

lcmd: cmd ';' lcmd
    |
    ;

cmd: block
    | TK_IDENTIFIER LEFT_ASSIGN exp
    | exp RIGHT_ASSIGN TK_IDENTIFIER
    | TK_IDENTIFIER '[' exp ']' LEFT_ASSIGN exp
    | exp RIGHT_ASSIGN TK_IDENTIFIER '[' exp ']'
    | KW_READ TK_IDENTIFIER
    | KW_PRINT print_args
    | KW_RETURN exp
    | KW_IF '(' exp ')' KW_THEN cmd with_else
    | KW_WHILE '(' exp ')' cmd
    ;

with_else: KW_ELSE cmd
    |
    ;

print_args: LIT_STRING print_args_rest
    | exp print_args_rest
    ;

print_args_rest: ',' LIT_STRING print_args_rest
    | ',' exp print_args_rest
    |
    ;

exp: node
    | exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | exp '<' exp
    | exp '>' exp
    | exp '|' exp
    | exp '&' exp
    | exp OPERATOR_LE exp
    | exp OPERATOR_GE exp
    | exp OPERATOR_EQ exp
    | exp OPERATOR_DIF exp
    | '~' exp
    | '#' exp
    | '$' exp
    | '(' exp ')'
    ;

node: TK_IDENTIFIER
    | TK_IDENTIFIER '[' exp ']'
    | literal
    | TK_IDENTIFIER '(' func_args ')'
    ;

func_args: exp func_args_rest
    |
    ;

func_args_rest: ',' exp func_args_rest
    |
    ;

%%

int yyerror (char *msg)
{
	printf("Syntax error at line: %d.\n", getLineNumber());
	exit(3);
}
