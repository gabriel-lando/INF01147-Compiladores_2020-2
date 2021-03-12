# Aluno: Gabriel Lando
#
# UFRGS - Compiladores B - Marcelo Johann - 2020/1 - Etapa 2
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#


etapa2: y.tab.o lex.yy.o main.o
	gcc y.tab.o lex.yy.o main.o -o etapa2

main.o: main.c
	gcc -c main.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.c: scanner.l
	lex scanner.l 

clean:
	rm -rf *.o lex.yy.c y.tab.c y.tab.h y.output etapa2