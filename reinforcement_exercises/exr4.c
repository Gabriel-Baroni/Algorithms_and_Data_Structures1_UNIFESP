// 1) Implemente as funções de inserção, busca e remoção para lista circular simplesmente encadeada.
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int info;
    struct no* prox;
}Lista; 

Lista* cria(){
    return NULL;
}

Lista* insere (Lista* l, int v){
    Lista* p = l;
    Lista* novo = malloc(sizeof(Lista));
    novo->info = v; 
    if(p==NULL){
        novo->prox = novo; 
        return novo; 
    }
    novo->prox = p; 
    return novo;
}

Lista* busca (Lista*l, int v){
    Lista* p = l;
    if(p==NULL){
        printf("Lista vazia");
        return l; 
    }
    do{
        if(p->info == v){
            return p;
        }
        p = p->prox; 
    }while(p!=l);
}

Lista* remover (Lista* l, int v){
    Lista* p = l;
    Lista* ant = NULL;
}



