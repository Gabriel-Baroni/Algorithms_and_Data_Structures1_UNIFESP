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
    do{
        p=p->prox;
    }while(p->prox!=l);
    p->prox = novo; 
    return novo;
}

Lista* busca (Lista*l, int v){
    Lista* p = l;
    if(p == NULL){
        printf("Lista vazia"); 
        return l; 
    }
    do{
        if(p->info == v){
            return p;
        }
        p = p->prox;
    }while(p!= l);

    return NULL; 
}

Lista* remover (Lista* l, int v){
    Lista* p = l;
    Lista* ant = NULL;
    if(p == NULL){
        printf("Lista vazia");
        return l; 
    }
    do{
        if(p->info == v){
            if(p->prox == l && ant == NULL){
                free(p);
                l=NULL;
                return l; 
            }
            if(ant == NULL){
                l = p->prox; 
                Lista* t = p;
                do{
                    t = t->prox;
                }while(t->prox !=p); 
                t->prox = l;
                free(p);
                return l; 
            }

            ant->prox = p->prox;  
            free(p); 
            return l; 
        }
        ant = p;
        p = p->prox; 
    }while(p != l); 
    return l; 
}



