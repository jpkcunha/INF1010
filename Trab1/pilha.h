typedef struct pilha Pilha;

void aborta(char* s);

Pilha* pilha_cria(void);

int pilha_vazia(Pilha* p);

void pilha_push(Pilha* p, void* info);

void* pilha_pop(Pilha* p);

void pilha_libera(Pilha* p);