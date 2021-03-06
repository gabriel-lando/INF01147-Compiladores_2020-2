// Aluno: Gabriel Lando

#define HASH_SIZE 997
#define STRING_SIZE 100

typedef struct hash_node {
    char * text;
    struct hash_node * next;

}
HASH_NODE;

void hashInit(void);
int hashAddress(char * text);
HASH_NODE * hashInsert(char * text);
HASH_NODE * hashFind(char * text);
void hashPrint(void);