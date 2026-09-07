// Considere as seguintes condições:
// 1. Use obrigatoriamente e exatamente como estão definidas as estruturas abaixo:
// /* Estrutura de um noh da lista encadeada */
// struct no {
// int info; // valor armazenado no noh
// struct no *prox; // ponteiro para o proximo noh
// };
// /* Estrutura das caixas */
// struct cx {
// No **caixa; // ponteiro para as caixas
// int N; // numero de caixas
// };
// Usando “typedef”, a estrutura “no” deve receber um codinome “No”. Já a estrutura “cx” deve
// receber o codinome “Caixa”.
// 2. O acesso a estrutura de “Caixa” se dará através de um ponteiro de “Caixa”, declarado na função
// “main” mas alocado na função “aloca_caixas” (veja abaixo).
// 3. Apenas as funções abaixo devem ser implementadas e obrigatoriamente usadas. Cada função
// deve ser nomeada e seguir exata e obrigatoriamente a descrição abaixo:
// (a) inicializa: função para inicializar a cabeça de uma lista, seu retorno é um endereço nulo;
// (b) aloca_caixas: recebe o número de caixas (N), aloca uma estrutura de “Caixas”, invoca a
// função “inicializa”, e retorna a referência da estrutura alocada;
// (c) h: recebe como parâmetro um item e o número de caixas (N), calcula e retorna um índice
// para uma caixa;
// (d) insere: recebe uma referência de “Caixa” e um item e o insere em uma lista de uma caixa;
// (e) retira: recebe uma referência de “Caixa” e um item. Se o item estiver em alguma lista,
// remove-o e retorna o endereço de memória do nó do item;
// (f) desaloca_lista: recebe a referência da cabeça de uma lista e desaloca essa lista;
// (g) desaloca_caixas: recebe uma referência de “Caixa”, invoca a função “desaloca_lista” e
// desaloca as caixas;
// (h) imprime: recebe uma referência de “Caixa” e exibe na tela as listas de cada caixa, da caixa
// 0 até N − 1.
// 4. Nenhuma variável global deve ser utilizada;
// 5. Toda memória alocada dinamicamente deve ser necessariamente desalocada1


#include <stdio.h>
#include <stdlib.h>


/* Estrutura de um noh da lista encadeada */
typedef struct no {
int info; // valor armazenado no noh
struct no *prox; // ponteiro para o proximo noh
}No;
/* Estrutura das caixas */
typedef struct cx {
No **caixa; // ponteiro para as caixas
int N; // numero de caixas
}Caixa;

No* incializa(){
    return NULL;
}

Caixa* aloca_caixas(int N){
    Caixa* l; 
    l = malloc(sizeof(Caixa)); //Aloca uma estrutura do tipo Caixa
    l->N = N; //Atribui o valor N ao campo N da caixa
    l->caixa = malloc(N*sizeof(No*)); //Aloca um vetor dinamico para N ponteiros de No e coloca o endereço no campo caixa 
    for(int i =0; i<N; i++){ //Para determinado número de caixa
        l->caixa[i] = incializa(); // inicializa as caixas (Cabecas das listas) dentro do campo caixa 
    }
    return l; 

 }

 int h(int k, int N){
    return k % N; //Calcula o mod entre o item e o número total de caixas
 }

 Caixa* insere(Caixa* l, int item){
    int indice = h(item, l->N); //Calcula o indice atravez da função h
    No* novo = malloc(sizeof(No)); //Aloca um espaço para um novo no
    novo->info = item; //Atribui ao campo info do novo nó o valor do item
    novo->prox = l->caixa[indice]; //Faz esse novo nó apontar onde a cabeça da respectiva caixa estava apontando
    l->caixa[indice] = novo; //A cabeça da nova caixa vai apontar para o novo nó
    return l; 
 }

 No* retira(Caixa* l, int item){
    int indice = h(item, l->N); //Calculo o índice para ver em qual caixa vou procurar
    No*p = l->caixa[indice]; //Declaro uma variável auxiliar p e atribuo o endereço apontado pela cabeça dessa lista
    No* ant = NULL; //Declaro outra variavel auxiliar que aponta para NULL
    while(p!= NULL && p->info != item){ //Enquanto não achar o item ou a lista não chegar ao fim 
        ant = p; //O ant aponta para onde o p estava apontando
        p=p->prox; //o p aponta para o proximo no
    }

    if(p==NULL){ //Se p for NULL, chegou ao fim da lista sem encontrar o item
        return NULL; 
    }

    if(ant == NULL){ //Se o ant for NULL, o primeiro elemento é para ser removido
        l->caixa[indice]=p->prox; //A cabeça dessa lista passa a apontar para o proximo elemento
    } else {
        ant->prox = p->prox; //O ant aponta para onde o p estava apontando
    }
    return p; //retorna o endereço de memória do p 
 }

 void desaloca_lista(No* cabeça){
    No* p = cabeça;  //Cria variavel auxiliar do tipo ponteiro de Nó e atribui o valor da cabeça para ela
    while(p!= NULL){ 
        No* t = p->prox;
        free(p); //Libera cada Nó da lista encadeada 
        p = t; 
    }
 }

 void desaloca_caixa(Caixa* l){
    for(int i=0; i<l->N; i++){
        desaloca_lista(l->caixa[i]); //Passa para a cabeça certa para a função desaloca_lista
    }
    free(l->caixa); //Depois de desalocar cada Nó, desaloca a propria lista
    free(l); //Por fim, desaloca a propria caixa
 }

 void imprime(Caixa* l){
    int i;
    No* p; 
    printf("\n"); 
    for(i=0; i<l->N; i++){ //Varre a lista de cabeças (caixas)
        for(p = l->caixa[i]; p != NULL; p=p->prox){ //Varre cada Nó da lista encadeada do indice i 
            printf("%d ", p->info);
        }
        printf("\n"); //Quebra a linha separando cada lista
    }
 }

 int main(){
    int N, m; 
    int item, item_busca;
    No* retirado; 
    Caixa *l; 
    //Input do número de caixas
    scanf("%d", &N);
    //Aloca a estrutura caixa
    l = aloca_caixas(N); 
    //Input do número de inteiros a serem inseridos
    scanf("%d", &m); 
    //Laço para pegar cada inteiro digitado e insiri-lo na sua respectiva caixa
    for(int i=0; i<m; i++){
        scanf("%d", &item);
        insere(l, item); 
    }
    //Input do item a ser buscado
    scanf("%d", &item_busca);
    //Atribuição do valor do item buscado (se foi retirado ou nao)
    retirado = retira(l, item_busca); 

    if(retirado == NULL){
        printf("%d", -1); 
    } else {
        printf("%d", retirado->info); 
        free(retirado); //Libera o item retirado
    }
    imprime(l); 
    desaloca_caixa(l); 

    return 0; 
 }