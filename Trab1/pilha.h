typedef struct pilha Pilha;

static const int PAR_ESQ = -3;
static const int PAR_DIR = -2;
static const int OP = -1;
static const int INT = 0;
static const int AD_SUB = 1;
static const int MULT_DIV = 2;

void aborta(char* s);

Pilha* pilha_cria(void);

int pilha_vazia(Pilha* p);

void pilha_push(Pilha* p, int tipo, void* x);

void* pilha_pop(Pilha* p, int* tipo, int *prioridade);

//char pilha_pop_op(Pilha* p);

void pilha_libera(Pilha* p);