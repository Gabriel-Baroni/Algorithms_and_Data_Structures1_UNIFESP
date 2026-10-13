#include <stdio.h>
#include <stdlib.h>
#include "interfaces/stack.h"

//Nó de uma lista simplesmente encadeada
typedef struct lista{
    int info;
    struct lista* prox; 

}Lista;

//Estrutura padrão de pilha com lista simplesmente encadeada
typedef struct pilha{
    Lista* prim;
}Pilha;

//Cria uma pilha vazia
Pilha* criar(){
    return NULL; 
}

//Insere um elemento no  topo da pilha
void push(Pilha* p, int v){
    Lista* novo = malloc(sizeof(Lista));
    novo->info = v;
    novo->prox = p->prim;
    p->prim = novo; 
}

//Retira um elemento do topo da pilha
int pop(Pilha* p){
    if(p->prim == NULL){ //Verifica se a pilha esta vazia
        printf("Pilha vazia");
        exit(1);
    }

    int v = p->prim->info;
    Lista* t = p->prim;
    p->prim = t->prox;
    free(p);
    return v; 
}

//Libera todos os elementos da pilha e a própria pilha
void liberar(Pilha*p){
    Lista* t = p->prim;
    while(t!= NULL){
        Lista* q = t->prox;
        free(t);
        t = q;
    }
    free(p);
}