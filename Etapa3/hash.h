// Aluno: Gabriel Lando
#ifndef __HASH_H__
#define __HASH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 997
#define STRING_SIZE 100

typedef struct hash_node {
    int type;
    char * text;
    struct hash_node * next;
}
HASH_NODE;

void hashInit(void);
int hashAddress(char * text);
HASH_NODE * hashInsert(int type, char * text);
HASH_NODE * hashFind(char * text);
void hashPrint(void);

#endif