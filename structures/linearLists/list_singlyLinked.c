#include <stdio.h>
#include <stdlib.h>
#include "interfaces/linearList.h"

typedef struct lista{
    int info;
    struct lista* prox;
}Lista; 


// Retorna o tamanho atual da lista percorrendo os nos
int tamanho(Lista* l) {
    int qtd = 0;
    const Lista* p = l;
    while (p != NULL) {
        qtd++;
        p = p->prox;
    }
    return qtd;
}

//Função para inicializar a lista
Lista* criar(){
    return NULL; 
}

Lista* inserir(Lista* l, int v, int pos){
    Lista* novo = malloc(sizeof(Lista));
    novo->info = v;
    Lista* p = l; 
    if(pos<0 || pos> tamanho(l)){ //Verifica se a posição da lista é válida
        printf("Posição inválida");
        return l; 
    }
    if(pos==0){ //Verifica se quer inserir no início
        novo->prox = l;
        return novo; 
    } 
    //Percorre até o nó anterior da posição a ser inserida
    for(int i = 0; i<pos-1; i++){
        p = p->prox; 
    }
    novo->prox = p->prox;
    p->prox = novo; 
  
    return l; 
}


int buscar(Lista* l, int v){
    if(l == NULL){ //Verifica se a lista esta vazia
        printf("Lisat vazia");
        return 0;
    }
    Lista* p = l;
    while(p!=NULL && p->info != v){ //Percorre a lista para encontrar o no
        p=p->prox; 
    }
    if(p==NULL){ // Verifica se foi encontrado o no
        printf("Valor não encontrado");
        return 0;
    } else{
        printf("Valor %d encontrado", v);
        return 1; 
    }
}

Lista* remover(Lista* l, int v){
     if(l == NULL){ //Verifica se a lista esta vazia
        printf("Lista vazia"); 
        return 0;
    }
    Lista* p = l; 
    Lista* ant = NULL;
    while(p!=NULL && p->info != v){ //Percorre a lista em busca do nó
        ant = p; 
        p=p->prox; 
    }
    if(p==NULL){ //Verifica se foi encontrado
        printf("Valor não encontrado");
        return l;
    }  

    if(ant == NULL){ //Verifica se é o primeiro elemento
        l= p->prox;
        free(p);

        return l; 
    }
    //Se for qualquer outro:
    ant->prox = p->prox;
    free(p);
    return l; 
}
//Libera todos os nós da lista
void liberar(Lista* l){
    Lista* p = l;
    while(p!= NULL){
        Lista* t = p->prox;
        free(p);
        p=t;
    }
}


