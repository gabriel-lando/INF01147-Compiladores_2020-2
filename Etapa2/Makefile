# Aluno: Gabriel Lando
#
# UFRGS - Compiladores B - Marcelo Johann - 2020/1 - Etapa 2
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa2: y.tab lex.yy.c main.c hash.c
	gcc -o etapa2 lex.yy.c hash.c
lex.yy.c: scanner.l
	lex scanner.l
y.tab: parser.y
	yacc -v parser.y -d

clean:
	rm -rf lex.yy.c y.tab.h y.tab.c etapa2 y.output
