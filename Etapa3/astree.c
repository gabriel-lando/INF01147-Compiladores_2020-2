// Aluno: Gabriel Lando

#include "astree.h"

ASTREE_NODE * AstreeCreate(int type, HASH_NODE * symbol, ASTREE_NODE * son0, ASTREE_NODE * son1, ASTREE_NODE * son2, ASTREE_NODE * son3) {
    ASTREE_NODE * node = (ASTREE_NODE * ) calloc(1, sizeof(ASTREE_NODE));
    node -> type = type;
    node -> symbol = symbol;
    node -> sons[0] = son0;
    node -> sons[1] = son1;
    node -> sons[2] = son2;
    node -> sons[3] = son3;

    return node;
}

void AstreePrint(int level, ASTREE_NODE * node) {
    if (node == 0) return;

    for (int i = 0; i < level; ++i)
        fprintf(stderr, "  ");

    fprintf(stderr, "AST (");
    switch (node -> type) {
    case AST_SYMBOL:
        fprintf(stderr, "AST_SYMBOL,");
        break;
    case AST_ADD:
        fprintf(stderr, "AST_ADD,");
        break;
    case AST_SUB:
        fprintf(stderr, "AST_SUB,");
        break;
    case AST_MULT:
        fprintf(stderr, "AST_MULT,");
        break;
    case AST_DIV:
        fprintf(stderr, "AST_DIV,");
        break;
    case AST_LESS:
        fprintf(stderr, "AST_LESS,");
        break;
    case AST_GREATER:
        fprintf(stderr, "AST_GREATER,");
        break;
    case AST_LE:
        fprintf(stderr, "AST_LE,");
        break;
    case AST_GE:
        fprintf(stderr, "AST_GE,");
        break;
    case AST_EQ:
        fprintf(stderr, "AST_EQ,");
        break;
    case AST_DIF:
        fprintf(stderr, "AST_DIF,");
        break;
    case AST_OR:
        fprintf(stderr, "AST_OR,");
        break;
    case AST_AND:
        fprintf(stderr, "AST_AND,");
        break;
    case AST_NOT:
        fprintf(stderr, "AST_NOT,");
        break;
    case AST_IFT:
        fprintf(stderr, "AST_IFT,");
        break;
    case AST_IFTE:
        fprintf(stderr, "AST_IFTE,");
        break;
    case AST_WHILE:
        fprintf(stderr, "AST_WHILE,");
        break;
    case AST_PRINT:
        fprintf(stderr, "AST_PRINT,");
        break;
    case AST_READ:
        fprintf(stderr, "AST_READ,");
        break;
    case AST_RETURN:
        fprintf(stderr, "AST_RETURN,");
        break;
    case AST_LCMD:
        fprintf(stderr, "AST_LCMD,");
        break;
    case AST_DECFUNC:
        fprintf(stderr, "AST_DECFUNC,");
        break;
    case AST_VARDEC:
        fprintf(stderr, "AST_VARDEC,");
        break;
    case AST_ASSIGN:
        fprintf(stderr, "AST_ASSIGN,");
        break;
    case AST_ASSIGNARRAY:
        fprintf(stderr, "ASSIGNARRAY,");
        break;
    case AST_ARRAY:
        fprintf(stderr, "AST_ARRAY,");
        break;
    case AST_BLOCK:
        fprintf(stderr, "AST_BLOCK,");
        break;
    case AST_PARENTH:
        fprintf(stderr, "AST_PARENTH,");
        break;
    case AST_DECFUNC_VOID:
        fprintf(stderr, "AST_DECFUNC_VOID,");
        break;
    case AST_VETDEC:
        fprintf(stderr, "AST_VETDEC,");
        break;
    case AST_DEC:
        fprintf(stderr, "AST_DEC,");
        break;
    case AST_DEC_PARAM:
        fprintf(stderr, "AST_DEC_PARAM,");
        break;
    case AST_DEC_PARAM2:
        fprintf(stderr, "AST_DEC_PARAM2,");
        break;
    case AST_PRINT_PARAM:
        fprintf(stderr, "AST_PRINT_PARAM,");
        break;
    case AST_INT:
        fprintf(stderr, "AST_INT,");
        break;
    case AST_BOOL:
        fprintf(stderr, "AST_BOOL,");
        break;
    case AST_POINTER:
        fprintf(stderr, "AST_POINTER,");
        break;
    case AST_CHAR:
        fprintf(stderr, "AST_CHAR,");
        break;
    case AST_ARRAY_INIT:
        fprintf(stderr, "AST_ARRAY_INIT,");
        break;
    case AST_ARRAY_INIT2:
        fprintf(stderr, "AST_ARRAY_INIT2,");
        break;
    case AST_FUNCCALL:
        fprintf(stderr, "AST_FUNCCALL,");
        break;
    case AST_FUNC_PARAM:
        fprintf(stderr, "AST_FUNC_PARAM,");
        break;
    case AST_FUNC_PARAM2:
        fprintf(stderr, "AST_FUNC_PARAM2,");
        break;
    case AST_VECSIZE:
        fprintf(stderr, "AST_VECSIZE,");
        break;
    case AST_DOLLAR:
        fprintf(stderr, "AST_DOLLAR,");
        break;
    case AST_HASH:
        fprintf(stderr, "AST_HASH");
    default:
        fprintf(stderr, "AST_UNKNOWN,");
        break;
    }

    if (node -> symbol != 0)
        fprintf(stderr, "%s)\n", node -> symbol -> text);
    else
        fprintf(stderr, "0)\n");

    for (int i = 0; i < MAX_SONS; i++)
        AstreePrint(level + 1, node -> sons[i]);

    return;
}

void UncompileAST(FILE * out, ASTREE_NODE * node) {

    if (node == NULL)
        return;

    switch (node -> type) {
    case AST_SYMBOL:
        fprintf(out, "%s", node -> symbol -> text);
        fflush(out);
        break;
    case AST_ADD:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " + ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_SUB:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " - ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_MULT:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " * ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_DIV:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " / ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_LESS:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " < ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_GREATER:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " > ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_LE:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " <= ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_GE:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " >= ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_EQ:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " == ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_DIF:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " != ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_OR:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " | ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_AND:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " & ");
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_NOT:
        fprintf(out, "~");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        break;
    case AST_IFT:
        fprintf(out, "if(");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, ") then \n");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        fprintf(out, " ");
        fflush(out);
        break;
    case AST_IFTE:
        fprintf(out, "if(");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, ") then ");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        fprintf(out, " else ");
        fflush(out);
        UncompileAST(out, node -> sons[2]);
        break;
    case AST_WHILE:
        fprintf(out, "while(");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, ")");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_PRINT:
        fprintf(out, "print ");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        break;
    case AST_READ:
        fprintf(out, "read ");
        fflush(out);
        fprintf(out, "%s", node -> symbol -> text);
        break;
    case AST_RETURN:
        fprintf(out, "return ");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        break;
    case AST_LCMD:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, ";\n");
        fflush(out);
        if (node -> sons[1] != NULL) {
            UncompileAST(out, node -> sons[1]);
        }
        break;
    case AST_DECFUNC:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " %s(", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        fprintf(out, ")");
        fflush(out);
        UncompileAST(out, node -> sons[2]);
        break;
    case AST_VARDEC:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " %s:", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        fprintf(out, ";");
        fflush(out);
        UncompileAST(out, node -> sons[2]);
        break;
    case AST_ASSIGN:
        fprintf(out, "%s<-", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        break;
    case AST_ASSIGNARRAY:
        fprintf(out, "%s[", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, "]<-");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_ARRAY:
        fprintf(out, "%s[", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, "]");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        if (node -> sons[2] != NULL) {
            UncompileAST(out, node -> sons[2]);
        }
        break;
    case AST_BLOCK:
        fprintf(out, "\n{\n");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, "}");
        fflush(out);
        break;
    case AST_PARENTH:
        fprintf(out, "(");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, ")");
        fflush(out);
        break;
    case AST_DECFUNC_VOID:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " %s()", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_VETDEC:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, "[");
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        fprintf(out, "] %s", node -> symbol -> text);
        fflush(out);
        if (node -> sons[2] != NULL) {
            fprintf(out, ": ");
            fflush(out);
            UncompileAST(out, node -> sons[2]);
        }
        fprintf(out, ";");
        fflush(out);
        break;
    case AST_DEC:
        if (node -> sons[1] != NULL) {
            UncompileAST(out, node -> sons[0]);
            fprintf(out, " \n");
            fflush(out);
            UncompileAST(out, node -> sons[1]);
        } else
            UncompileAST(out, node -> sons[0]);
        break;
    case AST_DEC_PARAM:
        UncompileAST(out, node -> sons[0]);
        fprintf(out, " %s", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[1]);
        break;
    case AST_DEC_PARAM2:
        fprintf(out, ", ");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        break;
    case AST_PRINT_PARAM:
        if (node -> sons[1] != NULL) {
            UncompileAST(out, node -> sons[0]);
            fprintf(out, ",");
            fflush(out);
            UncompileAST(out, node -> sons[1]);
        } else
            UncompileAST(out, node -> sons[0]);
        break;
    case AST_INT:
        fprintf(out, "int");
        fflush(out);
        break;
    case AST_BOOL:
        fprintf(out, "bool");
        fflush(out);
        break;
    case AST_POINTER:
        fprintf(out, "pointer");
        fflush(out);
        break;
    case AST_CHAR:
        fprintf(out, "char");
        fflush(out);
        break;
    case AST_ARRAY_INIT:
        UncompileAST(out, node -> sons[0]);
        if (node -> sons[1] != NULL) {
            fprintf(out, " ");
            fflush(out);
            UncompileAST(out, node -> sons[1]);
        }
        break;
    case AST_ARRAY_INIT2:
        UncompileAST(out, node -> sons[0]);
        if (node -> sons[1] != NULL) {
            fprintf(out, " ");
            fflush(out);
            UncompileAST(out, node -> sons[1]);
        }
        break;
    case AST_FUNCCALL:
        fprintf(out, "%s(", node -> symbol -> text);
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        fprintf(out, ")");
        fflush(out);
        break;
    case AST_FUNC_PARAM:
        UncompileAST(out, node -> sons[0]);
        if (node -> sons[1] != NULL) {
            fprintf(out, ",");
            fflush(out);
            UncompileAST(out, node -> sons[1]);
        }
        break;
    case AST_FUNC_PARAM2:
        UncompileAST(out, node -> sons[0]);
        if (node -> sons[1] != NULL) {
            fprintf(out, ",");
            fflush(out);
            UncompileAST(out, node -> sons[1]);
        }
        break;
    case AST_VECSIZE:
        fprintf(out, "%s", node -> symbol -> text);
        fflush(out);
        break;
    case AST_DOLLAR:
        fprintf(out, "$ ");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        break;
    case AST_HASH:
        fprintf(out, "# ");
        fflush(out);
        UncompileAST(out, node -> sons[0]);
        break;

    default:
        break;
    }
}