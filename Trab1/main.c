#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

#define MAX_STR 80
#define MAX_NUM 4

void le(char *s){
    if (s[0] == '\0') return;
    if (s[0]>='0' && s[0]<='9'){
        int i;
        for (i = 0; s[i]>='0' && s[i]<='9'; i++);
        char *aux = (char*)malloc(i+1);
        printf("Numero %d\n", atoi(strncpy(aux, s, i)));
        if (strlen(s)==i) return;
        le(s+i);
    }
    else{
        printf("Simbolooo\n");
        le(s+1);
    }
}

int main(void){
    //char *s = "456*(1234 + 456)/11";
    //le(s);
    Pilha *p = pilha_cria();
    printf("--> %d\n", pilha_vazia(p));
    return 0;
}