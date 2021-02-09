%{
    // Aluno: Gabriel Lando
    #include "tokens.h"
    #include "hash.h"

    char *s;
    char buffer[STRING_SIZE];

    int Running = 1;
    int lineNumber = 1;
%}

%x COMMENT
%x STRING

%%

"char"  { return KW_CHAR; }
"int"  { return KW_INT; }
"bool"  { return KW_BOOL; }
"pointer" { return KW_POINTER; }

"if"  { return KW_IF; }
"then"  { return KW_THEN; }
"else"  { return KW_ELSE; }
"while"  { return KW_WHILE; }
"read"  { return KW_READ; }
"print"  { return KW_PRINT; }
"return"  { return KW_RETURN; }

[,;:()\[\]\{\}+\-*/<>|&~$#]    { return yytext[0]; }

"<="    { return OPERATOR_LE; }
">="    { return OPERATOR_GE; }
"=="    { return OPERATOR_EQ; }
"!="    { return OPERATOR_DIF; }
"<-"    { return LEFT_ASSIGN; }
"->"    { return RIGHT_ASSIGN; }

"TRUE"  { return LIT_TRUE; }
"FALSE" { return LIT_FALSE; }

[0-9]*               { hashInsert(yytext); return LIT_INTEGER; }

\"      { BEGIN(STRING); s = buffer; }

\'.\'   {   yytext[0] = yytext[1]; 
            yytext[1] = '\0';
            hashInsert(yytext);
            return LIT_CHAR;
        }
        
[a-zA-Z_@][a-zA-Z0-9_@]*   { return TK_IDENTIFIER; }

"\n"    { ++lineNumber; }
[ \t]   //Do nothing
"//".*  //Do nothing
"/*"    { BEGIN(COMMENT); }

. { return TOKEN_ERROR; }

<COMMENT>.
<COMMENT>"\n"   { ++lineNumber; }
<COMMENT>"*/"   { BEGIN(INITIAL); }

<STRING>\\n     { *s++ = '\n'; }
<STRING>\\\"    { *s++ = '\"'; }
<STRING>\"      {	*s = 0;
                    BEGIN(INITIAL);
                    yytext = buffer;
                    hashInsert(yytext);
                    return LIT_STRING;
                }
<STRING>.       { *s++ = *yytext; }

%%

#include "main.c"

int getLineNumber() {
    return lineNumber;
}

int isRunning() {
    return Running;
}

int yywrap() {
    Running = 0;
    return 1;
}

void initMe() {
	Running = 1;
	lineNumber = 1;
	hashInit();
}
