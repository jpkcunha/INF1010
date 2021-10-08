#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

#define MAX_STR 80
#define MAX_NUM 4

void le(char *s, Pilha *p){
    if (s[0] == '\0') return;
    if (s[0]>='0' && s[0]<='9'){
        int i;
        for (i = 0; s[i]>='0' && s[i]<='9'; i++);
        
        char *aux = (char*)malloc(i+1);
        int *num = (int*)malloc(sizeof(int));
        *num = atoi(strncpy(aux, s, i));
        pilha_push(p, INT, num);
        free(aux);

        if (strlen(s)==i) return; //Se o número está no fim
        le(s+i, p);
    }
    else if (s[0] != ' '){
        char* c = (char*)malloc(sizeof(char));
        *c = s[0];
        pilha_push(p, OP, c);
        le(s+1, p);
    }
    else le(s+1, p);
}

int main(void){
    char *s = "1234 + 456";
    Pilha *p = pilha_cria();
    printf("--> %d\n", pilha_vazia(p));
    //le(s, p);
    printf("--> %d\n", pilha_vazia(p));
    printf("%d %d %d %d\n", OP, INT, AD_SUB, MULT_DIV);
    return 0;
}