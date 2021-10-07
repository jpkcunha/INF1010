#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

#define INT 1
#define OP 2
#define PARENT 3


typedef struct elemento {
    void* info;
    int tipo;
    struct elemento* prox;
} Elemento;

struct pilha{
    Elemento *topo;
};

void aborta(char* s){
    printf("%s",s);
    exit(1);
}


Pilha* pilha_cria(void){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) aborta("Erro de alocacao dinamica da pilha\n");
    p->topo = NULL;
    return p;
}

int pilha_vazia(Pilha* p){
    return (p->topo == NULL);
}

void pilha_push(Pilha* p, int tipo, void* x){
    Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
    if (novo == NULL) aborta("Erro de alocacao dinamica do novo elemento da pilha\n");

    novo->info = x;
    novo->prox = p->topo;
    p->topo = novo;
}

void* pilha_pop(Pilha* p){
    Elemento* t;
    void* val;
    if (pilha_vazia) aborta("Pilha vazia\n");

    t = p->topo;
    val = t->info;
    p->topo = t->prox;

    free(t->info);
    free(t);

    return val;
}

void pilha_libera(Pilha* p){
    free(p);
}