#include <stdio.h>
#include <stdlib.h>
#include "interfaces/queue.h"

//Nó de uma lista simplesmente encadeada
typedef struct lista{
    int info;
    struct lista* prox;
}Lista;

//Estrutura padrão de fila com lista simplesmente encadeada
typedef struct fila{
    Lista* ini;
    Lista* fim;
}Fila;

//Cria uma fila vazia
Fila* criar(){
    Fila* f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL; 
    return f; 
}

//Insere um elemento no final da fila
void insere(Fila* f, int v){
    Lista* novo = malloc(sizeof(Lista));
    novo->info = v;
    novo->prox = NULL;
    if(f->fim != NULL){
        f->fim->prox = novo;
    } else{
        f->ini = novo;
    }
    f->fim = novo; 
}

//Retira um elemento do início da fila
int retira(Fila* f){
    if(f->ini == NULL){  //Verifica se a fila esta vazia
        printf("A fila está vazia");
        exit(1); 
    }
    int v = f->ini->info;
    Lista* p = f->ini;
    f->ini = f->ini->prox; 
    if(f->ini == NULL){
        f->fim = NULL;
    }
    free(p);
    return v; 
}


//Libera todos os elementos da fila e a própria fila
void liberar(Fila* f){
    Lista* p = f->ini;
    while(p!=NULL){
        Lista* t = p->prox;
        free(p);
        p=t;
    }
    free(f); 
}
