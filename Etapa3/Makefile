# Aluno: Gabriel Lando
#
# UFRGS - Compiladores B - Marcelo Johann - 2020/1 - Etapa 3
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa3: lex.yy.o hash.o main.o y.tab.o astree.o
	gcc -o etapa3 lex.yy.o hash.o y.tab.o astree.o main.o

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

astree.o: astree.c
	gcc -c astree.c

lex.yy.o: lex.yy.c y.tab.o
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc parser.y -d

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm -f *.o etapa3 lex.yy.c y.tab.* y.output
