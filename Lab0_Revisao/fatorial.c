#include <stdio.h>
#include "fat.h"

int main(void){
    int a = 1, b = 3, c = 10;
    printf("a = %d\nb = %d\nc = %d\n", fat(a), fat(b), fat(c));
    return 0;
}