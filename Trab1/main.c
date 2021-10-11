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

void exibe(Token* t)
{
    printf("Criou: %d - %d - %d - %c\n", t->tipo, t->prioridade, t->num, t->op);
}

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
    //exibe(t);
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
        char *aux;
        Token *t = (Token*)pilha_pop(p);
        str_from_stack(s, p);
        if (t->tipo == INT)
        {
            int tam = (int)log10(t->num) + 2;
            aux = (char*)malloc(tam); //Tamanho = número de algarismos + 1
            snprintf(aux, tam,"%d",t->num);
        }
        else
        {
            aux = (char*)malloc(2);
            strcpy(aux, &(t->op));
        }
        if (strlen(s) != 0) strcat(s, " ");
        printf("String antes: %s\n", s);
        strcat(s, aux);
        printf("Concatenou str %s\n", aux);
        free(t); //Libera o token após salvá-lo na string
        printf("Liberou token\n");
        free(aux);
        printf("Liberou aux\n");
    }
}

char* ShuntingYard(char* s)
{
    //Inicializa as pilhas
    Pilha *input, *operator, *output;
    int tam = 0;
    Token *t1, *t2;

    input = pilha_cria();
    operator = pilha_cria();
    output = pilha_cria();
    stack_from_str(s, input);
    printf("Input feito: %s\n", s);

    while (!pilha_vazia(input))
    {
        t1 = (Token*)pilha_pop(input);
        if (t1->tipo == INT)
        {
            pilha_push(output, t1);
            tam++;
            printf("%d - Input --> output\n", tam);
            exibe(t1);
        }
        else if (t1->tipo == OP)
        {
            if (!pilha_vazia(operator))
            {
                t2 = (Token*)pilha_pop(operator);
                while((t2->tipo == OP) && (t2->prioridade >= t1->prioridade))
                {
                    pilha_push(output, t2);
                    tam++;
                    printf("%d - Operator --> output\n", tam);
                    exibe(t2);
                    if (pilha_vazia(operator)) break;
                    t2 = (Token*)pilha_pop(operator);
                }
                pilha_push(operator, t2);
            }
            pilha_push(operator, t1);
            printf("%d - Input --> operator\n", tam);
            exibe(t1);
        }
        else if (t1->tipo == PAR_ESQ)
        {
            pilha_push(operator, t1);
            printf("%d - Input --> operator PAR_ESQ\n", tam);
            exibe(t1);
        }
        else if (t1->tipo == PAR_DIR)
        {
            printf("%d - PAR_DIR\n", tam);
            if (pilha_vazia(operator)) aborta("A expressão inserida está desbalanceada\n");

            t2 = (Token*)pilha_pop(operator);
            while(t2->tipo != PAR_ESQ)
            {
                if (pilha_vazia(operator)) aborta("A expressão inserida está desbalanceada\n");
                pilha_push(output, t2);
                tam++;
                printf("%d - Operator --> output\n", tam);
                exibe(t2);
                t2 = (Token*)pilha_pop(operator);
            }
        }
        else aborta("Símbolo inválido\n");
    }

    while (!pilha_vazia(operator))
    {
        t1 = (Token*)pilha_pop(operator);
        if (t1->tipo == PAR_ESQ) aborta("A expressão inserida está desbalanceada\n");
        pilha_push(output, t1);
        tam++;
        printf("%d - Operator --> output\n", tam);
        exibe(t1);
    }
    
    char *postfix = (char*)malloc(2*tam+1);
    strcpy(postfix, "");
    str_from_stack(postfix, output);
    pilha_libera(input);
    pilha_libera(operator);
    pilha_libera(output);
    return postfix;
}


int main(void){
    char s[MAX_STR], *out;
    printf("Insira a expressão contendo números inteiros e as operações + - * /:\n");
    scanf("%[^\n]", s);
    out = ShuntingYard(s);
    printf("%s\n", out);
    free(out);
    return 0;
}