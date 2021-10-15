#include <stdio.h>
#include <stdlib.h>
#include "arvBin.h"
#include "info.h"

struct noArv
{
    void* info;
    struct noArv* sad;
    struct noArv* sae;
};

NoArv* arv_criavazia(void)
{
    return NULL;
}

NoArv* arv_cria(void *info, NoArv *sae, NoArv *sad)
{
    NoArv *nova = (NoArv*)malloc(sizeof(NoArv));
    if (nova == NULL) 
    {
        printf("Erro de alocacao dinamica da pilha\n");
        exit(1);
    }
    nova->info = info;
    nova->sae = sae;
    nova->sad = sad;
    return nova;

}

NoArv* arv_libera(NoArv *a)
{
    if (!arv_vazia(a))
    {
        arv_libera(a->sae);
        arv_libera(a->sad);
        free(a->info);
        free(a);
    }
    return NULL;
}

int arv_vazia(NoArv *a)
{
    return a==NULL;
}

int arv_pertence(NoArv *a, void *info)
{
    if (!arv_vazia(a)) return 0;
    else return a->info==info || arv_pertence(a->sae, info) || arv_pertence(a->sad, info);
}

//Imprime aninhada
void arv_imprime(NoArv * a) {
    if(!arv_vazia(a))
    {
        printf(" (");
        exibe(a->info);
        arv_imprime(a->sae);
        arv_imprime(a->sad);
        printf(" )");
        return;
    }
    printf(" ()");
}

int arv_calcula(NoArv *a)
{
    if (a == NULL) return 0;

    Token *t = (Token*)a->info;

    if (getTipo(t) == INT) return getNum(t);
    else if (getTipo(t) == OP)
    {
        char c = getOp(t);
        switch (c)
        {
            case '+': return arv_calcula(a->sae) + arv_calcula(a->sad);
            case '-': return arv_calcula(a->sae) - arv_calcula(a->sad);
            case '*': return arv_calcula(a->sae) * arv_calcula(a->sad);
            case '/': 
                if (arv_calcula(a->sad) == 0)
                {
                    printf("\nErro: divisão por zero\n");
                    return 0;
                }
                return arv_calcula(a->sae) / arv_calcula(a->sad);
            default:
                printf("Símbolo inválido na expressão postfix - %c\n",c);
                exit(1);
        }
    }
    else return 0;
    {
        printf("Tipo de caractere inválido\n");
        exit(1);
    }
}