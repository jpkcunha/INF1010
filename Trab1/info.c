#include <stdio.h>
#include <stdlib.h>
#include "info.h"

/* Cria token da expressão = números, +, -, *, /, ( e ) */
struct token
{
    int tipo, prioridade, num;
    char op;
};


void exibe(Token* t)
{
    if (t->tipo == INT) printf("%d", t->num);
    else printf("%c", t->op);
}

Token* token_cria(int tipo, void *info)
{
    Token *t = (Token*)malloc(sizeof(Token));
    if (t == NULL)
    {
        printf("Erro de alocacao dinamica do token\n");
        exit(1);
    }

    t->prioridade = INT;
    t->tipo = tipo;
    if (tipo){ //Operador
        char c = *((char*)info);
        switch (c)
        {
            case '+':
                t->prioridade = AD_SUB;
                break;
            case '-':
                t->prioridade = AD_SUB;
                break;
            case '*':
                t->prioridade = MULT_DIV;
                break;
            case '/':
                t->prioridade = MULT_DIV;
                break;
            case '(':
                break;
            case ')':
                break;
            default:
                printf("Símbolo inválido - %c\n",c);
                exit(1);
        }
        t->num = 0;
        t->op = c;
    }
    else
    {
        t->op = 0;
        t->num = *((int*)info);
    }
    //printf("Criou token: %d %d %d %c\n", t->tipo, t->prioridade, t->num, t->op);
    return t;
}

int getTipo(Token *t) { return t->tipo; }

int getPrioridade(Token *t) { return t->prioridade; }

int getNum(Token *t) { return t->num; }

char getOp(Token *t) { return t->op; }