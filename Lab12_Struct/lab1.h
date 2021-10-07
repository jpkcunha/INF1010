typedef struct aluno Aluno;

Aluno** inicializa(int n);
void verifica(int n, Aluno** l, int i);
void preenche(int n, Aluno** l, int i);
void retira(int n, Aluno** l, int i);
int busca(int n, int *vet, int x);
void imprime(int n, Aluno **l, int i);
void exibeLista(int n, Aluno** l);
void libera(Aluno** l);