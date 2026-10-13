//TAD: Pilha (Stack). Regra da estrutura - Last in, First out (LIFO)

//Tipo estruturado de pilha

typedef struct pilha Pilha;

//Tipo estruturado de Lista linear simplesmente encadeada
typedef struct lista Lista; 

//Funções exportadas

//Inicializa uma pilha vazia
Pilha* criar();

//Insere um elemento na pilha (sempre no topo)
void push(Pilha* p, int v);

//Remove um elemento da pilha (sempre no topo)
int pop(Pilha*p);

//Libera a estrutura da pilha e todos os seus elementos 
void liberar(Pilha* p);