#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pilha.h"

#define MAX_STR 81
#define MAX_NUM 4
#define PAR_ESQ -3
#define PAR_DIR -2
#define OP -1
#define INT 0
#define AD_SUB 1
#define MULT_DIV 2


/* Cria token da expressão = números, +, -, *, /, ( e ) */
typedef struct token
{
    int tipo, prioridade, num;
    char op;
} Token;

Token* token_cria(int tipo, void *info)
{
    Token *t = (Token*)malloc(sizeof(Token));
    if (t == NULL) aborta("Erro de alocacao dinamica do token\n");

    t->prioridade = INT;
    t->tipo = tipo;
    if (tipo){ //Operador
        char c = *((char*)info);
        switch (c){
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
                printf("%c - ",c);
                aborta("Símbolo invalido\n");
        }
        t->num = 0;
        t->op = c;
    }
    else
    {
        t->op = 0;
        t->num = *((int*)info);
    }
    return t;
}

void stack_from_str(char *s, Pilha *p)
{
    if (s[0] == '\0') return;
    if (s[0]>='0' && s[0]<='9')
    {
        int i;
        for (i = 0; s[i]>='0' && s[i]<='9'; i++); //i = qte de algarismos do número

        if (strlen(s)>i) stack_from_str(s+i, p);
        
        char *aux = (char*)malloc(i+1);
        int num = atoi(strncpy(aux, s, i));
        pilha_push(p, token_cria(INT, &num));
        free(aux);
    }
    else if (s[0] != ' ')
    { //Cada token pode ser separado por ' '
        stack_from_str(s+1, p);
        int tipo;
        if (s[0] == '(') tipo = PAR_ESQ;
        else if (s[0] == ')') tipo = PAR_DIR;
        else tipo = OP;
        pilha_push(p, token_cria(tipo, &s[0]));
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
    pilha_libera(input);
    pilha_libera(operator);
    return postfix;
}


int main(void){
    char s[MAX_STR], *out;
    printf("Insira a expressão contendo números inteiros e as operações + - * /:\n");
    scanf("%[^\n]", s);
    Pilha *p = pilha_cria();
    stack_from_str(s, p);

    //out = ShuntingYard(s);
    //printf("%s\n", out);
    return 0;
}