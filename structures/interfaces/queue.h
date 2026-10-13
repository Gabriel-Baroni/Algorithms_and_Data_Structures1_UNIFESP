//TAD: Filas (queue). Regra da estrutura - First in, First out (FIFO)

//tipo estruturado de fila

typedef struct fila Fila;

//Funções exportadas

//Cria uma pilha vazia
Fila* criar();

//Insere um elemento no final da fila
void insere(Fila* f, int v);

//Retira um elemento do início da fila
int retira(Fila* f);

//Libera a estrutura da fila e todos os seus elementos
void liberar(Fila* f); 