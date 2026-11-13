#include <stdio.h>
#include <stdlib.h>

//-=-=--=-=--=-=--=-=-ESTRUTURAS E FUNÇÕES PARA A PILHA-=-=--=-=--=-=--=-=-

typedef struct no{
    int info;
    struct no* prox;
}NoPilha;

typedef struct pilha{
    NoPilha* prim;
}Pilha;

Pilha* criar_pilha(){
    Pilha* p = malloc(sizeof(Pilha));
    p->prim = NULL;
    return p; 
} 

void push(Pilha* p, int v){
    NoPilha* novo = malloc(sizeof(NoPilha));
    novo->info = v;
    novo->prox = p->prim;
    p->prim = novo;  
}

int pop(Pilha* p){
    if(p->prim == NULL){
        return 0;
    }
    NoPilha* removido = p->prim;
    int v = removido->info; 
    p->prim = removido->prox;
    free(removido); 
    return v;
}

void liberar_pilha(Pilha* p){
    NoPilha* no = p->prim;
    while(no!=NULL){
        NoPilha* aux = no->prox;
        free(no);
        no = aux; 
    }
    free(p);
} 

//-=-=--=-=--=-=--=-=-ESTRUTURAS E FUNÇÕES PARA A FILA-=-=--=-=--=-=--=-=-
typedef struct no{
    int info;
    struct no* prox;
}NoFila;

typedef struct fila{
    NoFila* inicio;
    NoFila* fim;
}Fila; 

Fila* criar_fila(){
    Fila* f = malloc(sizeof(Fila));
    f->inicio == NULL;
    f->fim == NULL;
    return f;
}

void insere_fila(Fila* f, int v){
    NoFila* novo = malloc(sizeof(NoFila));
    novo->info = v;
    novo->prox = NULL;
    if(f->inicio == NULL){
        f->inicio = novo;
    }else{
        f->fim->prox = novo;
    }
    f->fim = novo; 
}

int retirar_fila(Fila* f){
    if(f->inicio == NULL){
        return 0;
    }
}


//-=-=--=-=--=-=--=-=-ESTRUTURAS E FUNÇÕES PARA A ABB-=-=--=-=--=-=--=-=-

//Estrutura de uma árvore
typedef struct arv{
    int info;
    struct arv* esq;
    struct arv* dir;
}Arv;

//Cria uma árvore vazia 
Arv* criar_vazia(){
    return NULL;
}

//Verifica se a árvore está vazia
int vazia (Arv* raiz){
    return raiz == NULL;
}

//Insere um elemento na árvore, seguindo as regras de uma ABB
Arv* insere(Arv* raiz, int v){
    if(vazia(raiz)){
        raiz = malloc(sizeof(Arv));
        raiz->info = v;
        raiz->esq = NULL;
        raiz->dir = NULL; 
    }else if(raiz->info > v){
        raiz->esq = insere(raiz->esq, v); 
    }else{
        raiz->dir = insere(raiz->dir, v);
    }
    return raiz; 
}

//Percorre a árvore em pré-ordem de forma recursiva
void preOrdem(Arv* raiz){
    if(vazia(raiz)){
        return;
    }
    printf("%d", raiz->info);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir); 
}

//Percorre a árvore em ordem de forma recursiva
void emOrdem(Arv* raiz){
    if(vazia(raiz)){
        return;
    }
    emOrdem(raiz->esq);
    printf("%d", raiz->info);
    emOrdem(raiz->dir); 
}

//Percorre a árvore em pós-ordem de froma iterativa
void posOrdem(Arv* raiz){
    if(vazia(raiz)){
        return;
    }
}

//Realiza busca binária na árvore
int buscar(Arv* raiz, int v){
    if(vazia(raiz)){
        return 0;
    }
    if(raiz->info == v){
        return 1;
    }else if(raiz->info > v){
        return buscar(raiz->esq, v); 
    } else{
        return buscar(raiz->dir, v); 
    }
}

int main(){
    //Declaração e inicialização de variáveis e estruturas
    int n, *lista, v;
    //Números de elementos a serem inseridos
    scanf("%d", &n);
    //Alocamento dinâmico de um vetor de int de tamanho n
    lista = malloc(n*sizeof(int));
    //Inicialização de uma árvore
    Arv* arvore = criar_vazia();

    //Preechendo o vetor com os valores
    for(int i=0; i<n; i++){
        scanf("%d", &lista[i]); 
    } 

    //Valor a ser buscado
    scanf("%d", &v);

    //Insere cada elemento na árvore
    for(int i=0; i<n; i++){
        arvore = insere(arvore, lista[i]);
    } 

    //Imprime em pré-ordem
    preOrdem(arvore);
    printf("\n");
    //Imprime em ordem
    emOrdem(arvore); 
    printf("\n");
    //Imprime em pós-ordem

    printf("\n");
    //Imprime em nível

    printf("\n");
    //Imprime em se existe ou não o elemento buscado
    printf("%d", buscar(arvore, v)); 
    return 0; 
}