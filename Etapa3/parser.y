%{
    // Aluno: Gabriel Lando

    #include <stdio.h>
    #include <stdlib.h>
    #include "hash.h"
    #include "astree.h"

    int yyerror (char *msg);
    int yylex(void);
    int getLineNumber(void);

    ASTREE_NODE * root = NULL;

%}

%union {
    HASH_NODE * symbol;
    ASTREE_NODE * astree;
}

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

%token <symbol>TK_IDENTIFIER

%token <symbol>LIT_INTEGER
%token <symbol>LIT_CHAR
%token <symbol>LIT_STRING
%token <symbol>LIT_TRUE
%token <symbol>LIT_FALSE

%token TOKEN_ERROR

%type <astree> program
%type <astree> declist
%type <astree> dec
%type <astree> dec_param
%type <astree> dec_param2
%type <astree> cmd_list
%type <astree> print
%type <astree> print_list
%type <astree> cmd
%type <astree> block
%type <astree> ctrl_flow
%type <astree> lit
%type <astree> type
%type <astree> array_init
%type <astree> array_init2
%type <astree> exp
%type <astree> func_param
%type <astree> func_param2

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

program: declist                                                {root=$1; AstreePrint(0,root);}
    ;

declist: 
    dec declist                                                 {$$=AstreeCreate(AST_DEC,0,$1,$2,0,0);}    
    |                                                           {$$=0;}
    ;

dec: 
    type TK_IDENTIFIER ':' lit ';'                              {$$=AstreeCreate(AST_VARDEC,$2,$1,$4,0,0);}
    | type TK_IDENTIFIER '('')'cmd_list                         {$$=AstreeCreate(AST_DECFUNC_VOID,$2,$1,$5,0,0);}
    | type TK_IDENTIFIER '('dec_param')' cmd_list               {$$=AstreeCreate(AST_DECFUNC,$2,$1,$4,$6,0);}
    | type '['LIT_INTEGER']' TK_IDENTIFIER array_init ';'       {$$=AstreeCreate(AST_VETDEC,$5,$1,AstreeCreate(AST_VECSIZE, $3, 0, 0, 0, 0),$6,0);}
    ;

dec_param:
    type TK_IDENTIFIER dec_param2                               {$$=AstreeCreate(AST_DEC_PARAM,$2,$1,$3,0,0);}
    ;

dec_param2:
    ',' dec_param                                               {$$=AstreeCreate(AST_DEC_PARAM2,0,$2,0,0,0);}
    |                                                           {$$=0;}
    ;

cmd_list: 
    cmd ';' cmd_list                                            {$$=AstreeCreate(AST_LCMD,0,$1,$3,0,0);}
    |                                                           {$$=0;}
    ;

print:
    print ',' print_list                                        {$$=AstreeCreate(AST_PRINT_PARAM,0,$1,$3,0,0);}
    | print_list                                                {$$=AstreeCreate(AST_PRINT_PARAM,0,$1,0,0,0);}
    ;

print_list:
    LIT_STRING                                                  {$$=AstreeCreate(AST_SYMBOL,$1,0,0,0,0);}
    |exp                                                        {$$=$1;}
    ;

cmd:
    TK_IDENTIFIER ':' exp                                       {$$=AstreeCreate(AST_ASSIGN,$1,$3,0,0,0);}
    | TK_IDENTIFIER LEFT_ASSIGN exp                             {$$=AstreeCreate(AST_ASSIGN,$1,$3,0,0,0);}
    | exp RIGHT_ASSIGN TK_IDENTIFIER                            {$$=AstreeCreate(AST_ASSIGN,$3,$1,0,0,0);}
    | TK_IDENTIFIER '[' exp ']' LEFT_ASSIGN exp                 {$$=AstreeCreate(AST_ASSIGNARRAY,$1,$3,$6,0,0);}
    | exp RIGHT_ASSIGN TK_IDENTIFIER '[' exp ']'                {$$=AstreeCreate(AST_ASSIGNARRAY,$3,$5,$1,0,0);}
    | KW_RETURN exp                                             {$$=AstreeCreate(AST_RETURN,0,$2,0,0,0);}
    | KW_READ TK_IDENTIFIER                                     {$$=AstreeCreate(AST_READ,$2,0,0,0,0);}
    | KW_PRINT print                                            {$$=AstreeCreate(AST_PRINT,0,$2,0,0,0);}
    | block                                                     {$$=$1;}
    | ctrl_flow                                                 {$$=$1;}
    |                                                           {$$=0;}
    ;

block:
    '{'cmd_list '}'                                             {$$=AstreeCreate(AST_BLOCK,0,$2,0,0,0);}
    ;

ctrl_flow:
    KW_IF '(' exp ')' KW_THEN cmd                               {$$=AstreeCreate(AST_IFT,0,$3,$6,0,0);}
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd                 {$$=AstreeCreate(AST_IFTE,0,$3,$6,$8,0);}
    | KW_WHILE '(' exp ')' cmd                                  {$$=AstreeCreate(AST_WHILE,0,$3,$5,0,0);}
    ;
    
lit:
    LIT_INTEGER                                                 {$$=AstreeCreate(AST_SYMBOL,$1,0,0,0,0);}
    | LIT_CHAR                                                  {$$=AstreeCreate(AST_SYMBOL,$1,0,0,0,0);}
    | LIT_TRUE                                                  {$$=AstreeCreate(AST_SYMBOL,$1,0,0,0,0);}
    | LIT_FALSE                                                 {$$=AstreeCreate(AST_SYMBOL,$1,0,0,0,0);}
    ;

type:
    KW_INT                                                      {$$=AstreeCreate(AST_INT,0,0,0,0,0);}
    | KW_BOOL                                                   {$$=AstreeCreate(AST_BOOL,0,0,0,0,0);}
    | KW_POINTER                                                {$$=AstreeCreate(AST_POINTER,0,0,0,0,0);}
    | KW_CHAR                                                   {$$=AstreeCreate(AST_CHAR,0,0,0,0,0);}
    ;

array_init:
    ':' lit array_init2                                         {$$=AstreeCreate(AST_ARRAY_INIT,0,$2,$3,0,0);}
    |                                                           {$$=0;}
    ;

array_init2:
    lit array_init2                                             {$$=AstreeCreate(AST_ARRAY_INIT2,0,$1,$2,0,0);}
    |                                                           {$$=0;}
    ;

exp:
    TK_IDENTIFIER                                               {$$=AstreeCreate(AST_SYMBOL,$1,0,0,0,0);}
    | TK_IDENTIFIER '[' exp ']'                                 {$$=AstreeCreate(AST_ARRAY,$1,$3,0,0,0);}
    | TK_IDENTIFIER '(' func_param ')'                          {$$=AstreeCreate(AST_FUNCCALL,$1,$3,0,0,0);}
    | '(' exp ')'                                               {$$=AstreeCreate(AST_PARENTH,0,$2,0,0,0);}
    | lit                                                       {$$ = $1;}
    | exp '+' exp                                               {$$=AstreeCreate(AST_ADD,0,$1,$3,0,0);}
    | exp '-' exp                                               {$$=AstreeCreate(AST_SUB,0,$1,$3,0,0);}
    | exp '*' exp                                               {$$=AstreeCreate(AST_MULT,0,$1,$3,0,0);}
    | exp '/' exp                                               {$$=AstreeCreate(AST_DIV,0,$1,$3,0,0);}
    | exp '>' exp                                               {$$=AstreeCreate(AST_GREATER,0,$1,$3,0,0);}
    | exp '<' exp                                               {$$=AstreeCreate(AST_LESS,0,$1,$3,0,0);}
    | exp '|' exp                                               {$$=AstreeCreate(AST_OR,0,$1,$3,0,0);}
    | exp '&' exp                                               {$$=AstreeCreate(AST_AND,0,$1,$3,0,0);}
    | '~' exp                                                   {$$=AstreeCreate(AST_NOT,0,$2,0,0,0);}
    | '$' exp                                                   {$$=AstreeCreate(AST_DOLLAR,0,$2,0,0,0);}
    | '#' exp                                                   {$$=AstreeCreate(AST_HASH,0,$2,0,0,0);}
    | exp OPERATOR_LE exp                                       {$$=AstreeCreate(AST_LE,0,$1,$3,0,0);}
    | exp OPERATOR_GE exp                                       {$$=AstreeCreate(AST_GE,0,$1,$3,0,0);}
    | exp OPERATOR_EQ exp                                       {$$=AstreeCreate(AST_EQ,0,$1,$3,0,0);}
    | exp OPERATOR_DIF exp                                      {$$=AstreeCreate(AST_DIF,0,$1,$3,0,0);}
    ;

func_param:
    exp func_param2                                             {$$=AstreeCreate(AST_FUNC_PARAM,0,$1,$2,0,0);}
    |                                                           {$$=0;}
    ;

func_param2:
    ',' func_param                                              {$$=AstreeCreate(AST_FUNC_PARAM2,0,$2,0,0,0);}
    |                                                           {$$=0;}
    ;

%%

int yyerror (char *msg)
{
    printf("Syntax error at line: %d.\n", getLineNumber());
    exit(3);
}

ASTREE_NODE * GetAST(){
    return root;
}
