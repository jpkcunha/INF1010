#define INT 1
#define OP 2
#define PARENT 3

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct elemento {
    int info;
    struct elemento* prox;
} Elemento;

struct pilha{
    Elemento *topo;
}

void erro(char *s){
    printf("%s",s);
    exit(EXIT_FAILURE);
};


Pilha* pilha_cria(void){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) erro("Erro de alocacao dinamica da pilha\n");
    p->topo = NULL;
    return p;
}

int pilha_vazia(Pilha *p){
    return (p->topo == NULL);
}

void pilha_push(Pilha* p, int tipo, void x){
    Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
    if (novo == NULL) erro("Erro de alocacao dinamica do novo elemento da pilha\n");

    novo->info = x;
    novo->prox = p->topo;
    p->topo = novo;
}

void pilha_libera(Ponto* p){
    free(p);
}