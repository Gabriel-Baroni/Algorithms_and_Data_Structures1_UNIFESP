//TAD: Lista linear

//Tipo estruturado de lista linear
typedef struct lista Lista; 

//Funções exportadas

// Inicializa uma lista e seus campos
Lista* criar(); 

// Insere um elemento em uma posição específica na lista
Lista* inserir(Lista* l, int v, int pos);

// Busca um elemento na lista e retorna se 1 caso exista e zero caso contrário
int buscar(Lista*l, int valor);

//Remove um elemento específico da lista na sua primeira ocorrência
Lista* remover(Lista* l, int valor);

//Desaloca toda a memória alocada na utilização da estrutura
void liberar(Lista* l);