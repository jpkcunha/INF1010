#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pilha.h"
#include "info.h"
#include "arvBin.h"


Pilha* stack_from_str(char *s)
{
    Pilha *p = pilha_cria();
    int cont = 0;
    while (s[0] != '\0')
    {
        //printf("%d - leu %c\n", cont, s[0]);
        if (s[0]>='0' && s[0]<='9')
        {
            int i;
            for (i = 0; s[i]>='0' && s[i]<='9'; i++); //i = qte de algarismos do número

            //Cria número a partir da string
            char *aux = (char*)malloc(i+1);
            int num = atoi(strncpy(aux, s, i));
            //printf("-> Num: %d\n", num);

            //Coloca na pilha
            pilha_push(p, token_cria(INT, &num));
            free(aux);

            if (strlen(s)>i) s += i; // Se o número for a última coisa da string
            else s += 1;
            cont ++;
        }
        else if (s[0] != ' ')
        { //Cada token pode ser separado por ' '
            
            char c = s[0];
            //printf("-> Op: %c\n", c);
            int tipo;
            if (s[0] == '(') tipo = PAR_ESQ;
            else if (s[0] == ')') tipo = PAR_DIR;
            else tipo = OP;
            pilha_push(p, token_cria(tipo, &s[0]));
            s += 1;
            cont ++;
        }
        else s += 1;
    }

    Pilha *final = pilha_cria();
    while (!pilha_vazia(p)) pilha_push(final, pilha_pop(p));
    //printf("\n->Criou pilha\n\n");
    pilha_libera(p);
    return final;

}


void str_from_stack(char *s, Pilha *p)
{
    while(!pilha_vazia(p))
    {
        char *aux;
        Token *t = (Token*)pilha_pop(p);
        //exibe(t);
        //printf("\n");
        str_from_stack(s, p);
        if (getTipo(t) == INT)
        {
            int tam = (int)log10(getNum(t)) + 2;
            aux = (char*)malloc(tam); //Tamanho = número de algarismos + 1
            snprintf(aux, tam,"%d",getNum(t));
            //printf("aux = '%s'\n", aux);
        }
        else
        {
            aux = (char*)malloc(2);
            snprintf(aux, 2,"%c",getOp(t));
            //printf("aux = '%s'\n", aux);
        }
        if (strlen(s) != 0) strcat(s, " ");
        strcat(s, aux);
        free(t); //Libera o token após salvá-lo na string
        free(aux);
    }
    return;
}


Pilha* ShuntingYard(char* s)
{
    //Inicializa as pilhas
    Pilha *input, *operator, *output;
    int tam = 0;
    Token *t1, *t2;

    input = stack_from_str(s);
    operator = pilha_cria();
    output = pilha_cria();
    
    while (!pilha_vazia(input))
    {
        t1 = (Token*)pilha_pop(input);
        if (getTipo(t1) == INT)
        {
            pilha_push(output, t1);
            tam++;
        }
        else if (getTipo(t1) == OP)
        {
            if (!pilha_vazia(operator))
            {
                t2 = (Token*)pilha_pop(operator);
                int cont = tam;
                while((getTipo(t2) == OP) && (getPrioridade(t2) >= getPrioridade(t1)))
                {
                    pilha_push(output, t2);
                    tam++;
                    if (pilha_vazia(operator)) break;
                    t2 = (Token*)pilha_pop(operator);
                }
                if (cont == tam || getTipo(t2) == PAR_ESQ) //Condições para recolocar na pilha operator
                {
                    pilha_push(operator, t2);
                }
            }
            pilha_push(operator, t1);
        }
        else if (getTipo(t1) == PAR_ESQ)
        {
            pilha_push(operator, t1);
        }
        else if (getTipo(t1) == PAR_DIR)
        {
            if (pilha_vazia(operator)) 
                {
                    printf("A expressão inserida está desbalanceada\n");
                    exit(1);
                }

            t2 = (Token*)pilha_pop(operator);
            while(getTipo(t2) != PAR_ESQ)
            {
                if (pilha_vazia(operator)) //Falta um '('
                {
                    printf("A expressão inserida está desbalanceada\n");
                    exit(1);
                }
                pilha_push(output, t2);
                tam++;
                t2 = (Token*)pilha_pop(operator);
            }
        }
        else
        {
            printf("Símbolo inválido - %c\n", getOp(t1));
            exit(1);
        }
    }
    
    while (!pilha_vazia(operator))
    {
        t1 = (Token*)pilha_pop(operator);
        
        if (getTipo(t1) == PAR_ESQ) //Falta um ')'
        {
            printf("A expressão inserida está desbalanceada\n");
            exit(1);
        }
        
        pilha_push(output, t1);
        tam++;
    }
    
    pilha_libera(input);
    pilha_libera(operator);
    
    return output;
}


NoArv* ArvoreExpressao(char *s)
{
    Pilha *p = pilha_cria();
    NoArv *a;
    int cont = 1;

    while (s[0] != '\0')
    {
        //printf("%d - leu %c\n", cont, s[0]);
        if (s[0]>='0' && s[0]<='9')
        {
            int i;
            for (i = 0; s[i]>='0' && s[i]<='9'; i++); //i = qte de algarismos do número

            char *aux = (char*)malloc(i+1);
            int num = atoi(strncpy(aux, s, i));
            //printf("-> Num: %d\n", num);
            //Cria árvore com o token como raiz e insere no topo da pilha
            a = arv_cria(token_cria(INT, &num), arv_criavazia(), arv_criavazia());
            //arv_imprime(a);
            //printf("\nCriou árvore de num\n");
            pilha_push(p, a);
            //printf("Push num successful\n");
            free(aux);
            
            if (strlen(s)>i) s += i;
            else s += 1;
            cont += 1;
        }
        else if (s[0] != ' ')
        { //Cada token pode ser separado por ' '
            
            char c = s[0];
            //printf("-> Op: %c\n", c);
            NoArv *sae, *sad;

            sad = (NoArv*)pilha_pop(p);
            sae = (NoArv*)pilha_pop(p);
            a = arv_cria(token_cria(OP, &c), sae, sad);
            //a = arv_cria(token_cria(OP, &c), arv_criavazia(), arv_criavazia());
            //arv_imprime(a);
            //printf("\nCriou árvore de op\n");
            pilha_push(p, a);
            //printf("Push op successful\n");
            s += 1;
            cont += 1;
        }
        else s += 1;
    }
    //printf("Saiu do while\n");
    a = (NoArv*)pilha_pop(p);
    pilha_libera(p);
    return a;
}


int main(void){
    
    char *in[] ={"3 + 2 * 3",
                 "10 * 2 - 2 * 5",
                 "7 + 3 / 2",
                 "2 * 6 + 3 / 8",
                 "2 + (3 * (8 - 4))",
                 "18 / 2 * 5 + 6 - 4",
                 "3 + (16 - 4 * 3) - 6 / 2",
                 "(2 - 3 + 1) / (2 - 2)",
                 "((18 + 3 * 2) / 8 + 5 * 3) / 6",
                 "16 / 4 * (4)"};
  
    
    for (int i = 0; i<10; i++) {
        printf("Infix: %s\n", in[i]);
        Pilha *p = ShuntingYard(in[i]);
        
        char *out = (char*)malloc(MAX_STR);
        str_from_stack(out, p);
        printf("Postfix: '%s'\n", out);

        NoArv* a = ArvoreExpressao(out);
        arv_imprime(a);
        printf("\nResultado: %d\n\n", arv_calcula(a));    

        arv_libera(a);
        free(out);
        pilha_libera(p);
    }

    printf("Feito!\n");
    return 0;
}
