#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct elemento
{
    void* info;
    struct elemento* prox;
} Elemento;


struct pilha
{
    Elemento *topo;
};



Pilha* pilha_cria(void)
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) 
    {
        printf("Erro de alocacao dinamica da pilha\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

int pilha_vazia(Pilha* p)
{
    return (p->topo == NULL);
}


void pilha_push(Pilha* p, void* info)
{
    Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
    if (novo == NULL)
    {
        printf("Erro de alocacao dinamica do elemento\n");
        exit(1);
    }
    novo->info = info;
    novo->prox = p->topo;
    p->topo = novo;
}

void* pilha_pop(Pilha* p)
{
    Elemento* t;
    void* val;
    if (pilha_vazia(p))
    {
        printf("Pilha vazia\n");
        exit(1);
    }
    t = p->topo;
    val = t->info;
    p->topo = t->prox;
    free(t);
    return val;    
}

void pilha_libera(Pilha* p)
{
    Elemento *t, *q = p->topo;
    while (q != NULL)
    {
        t = q->prox;
        free(q);
        q = t;
    }
    free(p);
}