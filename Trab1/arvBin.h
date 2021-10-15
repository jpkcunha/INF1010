typedef struct noArv NoArv;

NoArv* arv_criavazia(void);

NoArv* arv_cria(void *info, NoArv *sae, NoArv *sad);

NoArv* arv_libera(NoArv *a);

int arv_vazia(NoArv *a);

int arv_pertence(NoArv *a, void *info);

void arv_imprime(NoArv *a);

int arv_calcula(NoArv *a);