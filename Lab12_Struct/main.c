#include <stdio.h>
#include <stdlib.h>
#include "lab1.h"

int main(void){
    int n = 4;
    Aluno** lista = inicializa(n);

    preenche(n, lista, 0);
    preenche(n, lista, 1);
    preenche(n, lista, 2);
    
    exibeLista(n, lista);

    retira(n, lista, 0);
    retira(n, lista, 1);
    retira(n, lista, 2);
    libera(lista);

    return 0;
}