%{
    // Aluno: Gabriel Lando
    #include "hash.h"
    #include "astree.h"
    #include "y.tab.h"

    char *s;
    char buffer[STRING_SIZE];

    int Running = 1;
    int lineNumber = 1;
%}

%x COMMENT

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

"true"  { yylval.symbol = hashInsert(LIT_TRUE,yytext); return LIT_TRUE; }
"false" { yylval.symbol = hashInsert(LIT_FALSE,yytext); return LIT_FALSE; }

[0-9]*               { yylval.symbol = hashInsert(LIT_INTEGER,yytext); return LIT_INTEGER; }

'(\\.|[^'\n])*\'	{ if (yyleng==3) { 
                        yylval.symbol = hashInsert(LIT_CHAR,yytext);
                        return LIT_CHAR;
                      } else return TOKEN_ERROR; }

\"(\\.|[^\"\n])*\" 	 { yylval.symbol = hashInsert(LIT_STRING,yytext); return LIT_STRING; }
        
[a-z_A-Z]+[a-zA-Z_0-9]*     { if( yytext[-1]!='"') {
                                yylval.symbol = hashInsert(TK_IDENTIFIER,yytext); 
                                return TK_IDENTIFIER;
                            } } 

"\n"    { ++lineNumber; }
[ \t]   //Do nothing
"//".*  //Do nothing
"/*"    { BEGIN(COMMENT); }

. { return TOKEN_ERROR; }

<COMMENT>.
<COMMENT>"\n"   { ++lineNumber; }
<COMMENT>"*/"   { BEGIN(INITIAL); }

%%

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
