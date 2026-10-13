#include <stdio.h>
#include <stdlib.h>
#include "interfaces/linearList.h"

//Estrutura padrão de lista duplamente encadeada
typedef struct lista{
    int info;
    struct lista* prox;
    struct lista* ant; 
}Lista;

//Criar uma lista vazia
Lista* criar(){
    return NULL; 
}
//Função que retorna o número de elementos da lista
int tamanho(Lista*l){
    int qtd=0;
    Lista* p = l; 
    while(p!= NULL){
        p=p->prox;
        qtd++;
    }
    return qtd; 
}

Lista* inserir(Lista* l, int v, int pos){

    if(pos<0 || pos>tamanho(l)){//Verifica se a posição é válida
        printf("Posição inválida");
        return l; 
    }

    Lista* novo = malloc(sizeof(Lista));
    novo->info = v; 
    if(pos==0){ //Verifica se quer inserir no primeiro elemento
        novo->prox = l;
        novo->ant = NULL; 
        l->ant = novo; 
        return novo; 
    }
    Lista* p = l;
    for(int i = 0; i<pos-1; i++){ //Percorre até a posição desejada
        p=p->prox;
    }
    //Ajusta os ponteiros
    novo->prox = p->prox; 
    novo->ant = p;
    if(p->prox!= NULL){ //Verifica se o proximo elemento nao é NULL
        p->prox->ant = novo;
    }
    p->prox = novo; 
    return l; 
}

int buscar(Lista* l, int v){
    Lista* p = l;
    while(p!=NULL && p->info != v){
        p = p->prox;
    }
    if(p=NULL){
        printf("Valor não encontrado");
        return 0;
    }
    printf("Valor encontrado");
    return 1;
}

Lista* remover(Lista* l, int v){
    Lista* p = l;
    if(l==NULL){ // Verifica se a lisa não é vazia
        printf("Lista vazia");
        return l;
    }
    while(p!=NULL && p->info != v){
        p=p->prox;
    }
    if(p==NULL){ //Verifica se o elemento está na lista
        printf("Valor não encontrado");
        return l;
    }
    if(p==l){ //Verifica se é o primeiro elemento
        l=p->prox;
        if(l!=NULL){
            p->ant = NULL;
        }
        free(p);
        return l; 
    }
    //Se for qualquer outro caso:
    p->ant->prox = p->prox;
    if(p->prox != NULL){ 
        p->prox->ant = p->ant; 
    }
    free(p);
    return l; 
}

//Libera todos os nós da lista
void liberar(Lista* l){
    Lista* p = l;
    while(p!=NULL){
        Lista* t = p->prox;
        free(p);
        p=t;
    }
}