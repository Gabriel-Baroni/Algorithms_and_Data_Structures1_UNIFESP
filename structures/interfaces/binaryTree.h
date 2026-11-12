//TAD: Árvore binária (Binary tree)

//Estrutura padrao de uma árvore binária 
typedef struct arv Arv; 

//Cria uma árvore vazia
Arv* cria_vazia();

//Cria uma árvore com seus elementos
Arv* cria(Arv* raiz, Arv* sae, Arv* sad, int v);

//Busca em uma árvore
Arv* buscar(Arv* raiz, int v);

//Insere em uma árvore
Arv* inserir(Arv* raiz, int v);

//Remove de uma árvore
Arv* remover(Arv* raiz, int v);

//Verifica se a áravore é vazia
Arv* vazia(Arv* raiz); 
