#include <stdio.h>
#include <stdlib.h>
#include "lab1.h"

struct aluno{
    int matricula;
    char nome[81], end[121], tel[21];
};

Aluno** inicializa(int n){
    Aluno ** l = (Aluno **)malloc(n*sizeof(Aluno*));
    for (int i = 0; i < n; i++)
        l[i] = NULL;
    return l;
}

void verifica(int n, Aluno** l, int i){
    if (i<0 || i>=n){
        printf("Indice fora do limite do vetor\n");
        exit(1);
    }
}

void preenche(int n, Aluno** l, int i){
    verifica(n, l, i);

    if (l[i]==NULL)
        l[i] = (Aluno*)malloc(sizeof(Aluno));
    
    printf("Insira a matricula: ");
    scanf("%d", &l[i]->matricula);
    printf("Insira o nome: ");
    scanf(" %[^\n]s", l[i]->nome);
    printf("Insira o endereco: ");
    scanf(" %[^\n]s", l[i]->end);
    printf("Insira o telefone: ");
    scanf(" %[^\n]s", l[i]->tel);
}

void retira(int n, Aluno** l, int i){
    verifica(n, l, i);

    if (l[i] != NULL){
        free(l[i]);
        l[i] = NULL;
    }
}

int busca(int n, int *vet, int x){
    if (n <= 0)
        return -1;
    int meio = n/2;
    if (x < vet[meio])
        return busca(meio, vet, x);
    else if (x > vet[meio]){
        int r = busca(n-1-meio, &vet[meio+1], x); //Busca no vetor a partir do meio
        if (r == -1) return -1;
        else return (meio + r + 1); //Conserta o índice da busca do vetor a partir do meio dele
    }
    else return meio;
}

void imprime(int n, Aluno **l, int i){
    verifica(n, l, i);
    
    if (l[i] != NULL){
        printf("Matrícula: %d\n", l[i]->matricula);
        printf("Nome: %s\n", l[i]->nome);
        printf("Endereço: %s\n", l[i]->end);
        printf("Telefone: %s\n", l[i]->tel);
    }
}

void exibeLista(int n, Aluno** l){
    for (int i = 0; i<n;i++)
    imprime(n, l, i);
}

void libera(Aluno** l){
    free(l);
}