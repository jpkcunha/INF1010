#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 20

typedef struct _heap Heap;
struct _heap {
    int max; /* tamanho maximo do heap */
    int pos; /* proxima posicao disponivel no vetor */
    int* info; /* vetor dos elementos do heap */
};

Heap* heap_cria(int max){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->max = max;
    heap->pos = 0;
    heap->info = (int*)malloc(max*sizeof(int));
    return heap;
}

static void troca(int a, int b, int* v) {
    int f = v[a];
    v[a] = v[b];
    v[b] = f;
}

static void corrige_acima(Heap* heap, int pos) {
    while (pos > 0){
        int pai = (pos-1)/2;
        if (heap->info[pai] > heap->info[pos])
            troca(pos,pai,heap->info);
        else break;
        pos = pai;
    }
}

static void corrige_abaixo(Heap* heap){
    int pai=0;
    while (2*pai+1 < heap->pos){
        int filho_esq=2*pai+1, filho_dir=2*pai+2, filho;
        if (filho_dir >= heap->pos) filho_dir=filho_esq;
        if (heap->info[filho_esq] < heap->info[filho_dir])
            filho=filho_esq;
        else filho=filho_dir;
        if (heap->info[pai] > heap->info[filho])
            troca(pai,filho,heap->info);
        else break;
        pai = filho;
    }
}


void heap_insere(Heap* heap, int info){
    if ( heap->pos < heap->max ) {
        heap->info[heap->pos] = info;
        corrige_acima(heap, heap->pos);
        heap->pos++;
    } 
    else printf("Heap Cheio!\n"); 
}



int heap_remove(Heap* heap) {
    if (heap->pos>0) {
        int topo = heap->info[0];
        heap->info[0] = heap->info[heap->pos-1];
        heap->pos--;
        corrige_abaixo(heap);
        return topo;
    }
    else {
        printf("Heap Vazio!");
        return -1;
    }
}
void exibe(Heap *heap){
    for (int i = 0; i < heap->pos; i++) printf("%d ", heap->info[i]);
    printf("\n");
}

void heapify(Heap* heap, int pai) { 
    //printf("Heapify %d\n", heap->info[pai]);
    int menor = pai; // Inicializa menor sendo a raiz
    int filho_esq = 2 * pai + 1;
    int filho_dir = 2 * pai + 2;
    if (filho_esq < heap->pos && heap->info[filho_esq] > heap->info[menor]) 
        menor = filho_esq; 
    if (filho_dir < heap->pos && heap->info[filho_dir] > heap->info[menor]) 
        menor = filho_dir; 
    if (menor != pai) { // menor não é o pai
        troca(pai, menor, heap->info);
        //printf("Trocou %d com %d\n", heap->info[pai], heap->info[menor]);
        //exibe(heap);
        heapify(heap, filho_esq); 
    } 
}


void constroi_heap(Heap* heap) 
{ 
    // índice do último nó intermediário (não-folha)
    int n = heap->pos;
    int startIdx = (n / 2) - 1; 
    int i;
    for (i = startIdx; i >= 0; i--) { 
        heapify(heap, i); //heapify minheap
    } 
}

void heapsort (Heap* heap){
    int i;
    int n = heap->pos;
    constroi_heap(heap);
    exibe(heap);
    //printf("constroi_heap =================\n\n");
    for (i = heap->pos - 1; i >= 1; i--) {
        troca(0, i, heap->info);
        //exibe(heap);
        heap->pos--;
        //printf("Heapsort - Trocou %d com %d\n", heap->info[0], heap->info[i]);
        
        //exibe(heap);
        heapify(heap, 0); //heapify maxheap
        exibe(heap);
        printf("\n");
    }
    heap->pos = n;
    }


int countSmaller(Heap* heap, int x, int pai){
    int filho_esq = 2 * pai + 1;
    int filho_dir = 2 * pai + 2;
    if (filho_esq >= heap->pos) {
        if (heap->info[pai] < x) {
            return 1;
        }
        else return 0;
    }
    else{
        if (heap->info[pai] < x) {
            return 1 + countSmaller(heap, x, filho_esq) + countSmaller(heap, x, filho_dir);
        }
        else return 0;
    }
}

int main(void){
    Heap *h = heap_cria(MAX);
    heap_insere(h, 10);
    heap_insere(h, 50);
    heap_insere(h, 20);
    heap_insere(h, 5);
    heap_insere(h, 60);
    heap_insere(h, 80);
    heap_insere(h, 15);
    exibe(h);
    heapsort(h);
    printf("Heap: %d/%d\n", h->pos, h->max);
    for (int i = 0; i < h->pos; i++) printf("-> %d\n", h->info[i]);
    printf("\n==> %d\n", countSmaller(h, 6, 0));
    printf("\n==> %d\n", countSmaller(h, 15, 0));
    printf("\n==> %d\n", countSmaller(h, 61, 0));
    printf("\n==> %d\n", countSmaller(h, 80, 0));
    printf("\n==> %d\n", countSmaller(h, 100, 0));
    return 0;
}