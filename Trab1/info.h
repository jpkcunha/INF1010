static const int MAX_STR = 81;
static const int MAX_NUM = 4;
static const int PAR_ESQ = -3;
static const int PAR_DIR = -2;
static const int OP = -1;
static const int INT = 0;
static const int AD_SUB = 1;
static const int MULT_DIV = 2;

typedef struct token Token;

void exibe(Token* t);

Token* token_cria(int tipo, void *info);

int getTipo(Token *t);

int getPrioridade(Token *t);

int getNum(Token *t);

char getOp(Token *t);