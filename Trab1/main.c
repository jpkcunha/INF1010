#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pilha.h"

#define MAX_STR 81
#define MAX_NUM 4

void stack_from_str(char *s, Pilha *p)
{
    if (s[0] == '\0') return;
    if (s[0]>='0' && s[0]<='9')
    {
        int i;
        for (i = 0; s[i]>='0' && s[i]<='9'; i++);

        if (strlen(s)>i) stack_from_str(s+i, p);
        
        char *aux = (char*)malloc(i+1);
        int *num = (int*)malloc(sizeof(int));
        *num = atoi(strncpy(aux, s, i));
        pilha_push(p, INT, num);
        free(aux);
    }
    else if (s[0] != ' ')
    { //Cada token pode ser separado por ' '
    
        stack_from_str(s+1, p);
        int tipo = OP;
        char* c = (char*)malloc(sizeof(char));
        *c = s[0];
        if (*c == '(') tipo = PAR_ESQ;
        else if (*c == ')') tipo = PAR_DIR;
        pilha_push(p, tipo, c);
    }
    else stack_from_str(s+1, p);
}

void str_from_stack(char *s, Pilha *p)
{
    while(!pilha_vazia(p))
    {
        int tipo, prioridade;
        char* aux;
        void* elem = pilha_pop(p, &tipo, &prioridade);
        str_from_stack(s, p);
        if (tipo == INT)
        {
            int tam, x = *((int*)elem);
            tam = (int)log10(x) + 2;
            aux = (char*)malloc(tam); //Tamanho = número de algarismos + 1
            snprintf(aux, tam,"%d",x);
        }
        else
        {
            char *x = (char*)elem;
            aux = (char*)malloc(1);
            strcpy(aux, x);
        }
        strcat(s, aux);
        free(elem);
        free(aux);
    }
}

char* ShuntingYard(char* s)
{
    //Inicializa as pilhas
    Pilha *input, *operator, *output;
    int t1, p1, t2, p2, tam = 0;
    void *elem, *op;

    input = pilha_cria();
    operator = pilha_cria();
    output = pilha_cria();
    stack_from_str(s, input);

    while (!pilha_vazia(input))
    {
        elem = pilha_pop(input, &t1, &p1);
        //switch (t1){
        if (t1 == INT)
        {
            pilha_push(output, t1, elem);
            tam++;
        }
        else if (t1 == OP)
        {
            if (!pilha_vazia(operator))
            {
                op = pilha_pop(operator, &t2, &p2);
                while(!pilha_vazia(operator) && t2 == OP && p2 >= p1)
                {
                    pilha_push(output, t2, op);
                    tam++;
                    op = pilha_pop(operator, &t2, &p2);
                }
                pilha_push(operator, t2, op);
            }
            pilha_push(operator, t1, elem);
        }
        else if (t1 == PAR_ESQ)
        {
            pilha_push(operator, t1, elem);
        }
        else if (t1 == PAR_DIR)
        {
            if (pilha_vazia(operator)) aborta("A expressão inserida está desbalanceada\n");

            op = pilha_pop(operator, &t2, &p2);
            while(t2 != PAR_ESQ)
            {
                if (pilha_vazia(operator)) aborta("A expressão inserida está desbalanceada\n");
                pilha_push(output, t2, op);
                op = pilha_pop(operator, &t2, &p2);
            }
            free(elem);
            free(op);
        }
        else aborta("Símbolo inválido\n");
    }

    while (!pilha_vazia(operator))
    {
        op = pilha_pop(operator, &t1, &p1);
        if (t1 == PAR_ESQ) aborta("A expressão inserida está desbalanceada\n");
        pilha_push(output, t1, op);
    }
    
    char *postfix = (char*)malloc(tam+1);
    str_from_stack(postfix, output);
    return postfix;
}


int main(void){
    char s[MAX_STR], *out;
    printf("Insira a expressão contendo números inteiros e as operações + - * /:\n");
    scanf("%[^\n]", s);
    Pilha *p = pilha_cria();
    stack_from_str(s, p);

    out = ShuntingYard(s);
    printf("%s\n", out);
    return 0;
}