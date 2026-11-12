#include <stdio.h>
#include <stdlib.h>

//Nó de uma árvore binária
typedef struct no{
    int info;
    struct no* esq;
    struct no* dir;
}No; 

//Função para criar uma árvore vazia
No* criar_vazia(){
    return NULL;
}

//Função para criar uma árvere não vazia
No* criar (No* raiz, No* sae, No* sad, int v){
    raiz->info = v; 
    raiz->dir = sad;
    raiz->esq = sae;
    return raiz;
}

//Função para imprimir em pré-ordem (RAIZ -> SAE -> SAD)
void preOrdem(No* raiz){
    if(!raiz == NULL){
        printf("%d", raiz->info);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

//Função para imprimir em ordem (SAE -> RAIZ -> SAD)
void ordem(No* raiz){
    if(!raiz ==NULL){
        ordem(raiz->esq);
        printf("%d", raiz->info);
        ordem(raiz->dir);
    }
}

//Função para percorrer em ordem (SAE -> SAD -> RAIZ)
void posOrdem(No* raiz){
    if(!raiz==NULL){
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d", raiz->info);
    }
}

//Função para liberar a árvore
No* liberar(No* raiz){
    if(!raiz == NULL){
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz); 
    }
    return NULL; 
}

//Função de busca de um elemento
int buscar(No* raiz, int v){
    if(raiz == NULL){
        return 0;
    }else{
        return raiz->info == v || buscar(raiz->esq, v) || buscar(raiz->dir, v); 
    }
}

//Função para verificar se uma árvore é vazia 
int vazia(No* raiz){
    return raiz == NULL;
}


