// 2) Implemente uma pilha dinâmica e suas operações
#include <stdio.h>
#include <stdlib.h>

//Estrutura padrão para uma lista simplesmente encadeada
typedef struct lista{
    float valor;
    struct lista* prox;
}Lista; 

//Estruta padrão para uma pilha dinamica
typedef struct pilha{
    Lista* primeiro; 
}Pilha;

//Função para criar uma pilha dinamica
Pilha* cria(){
    Pilha* pilha = malloc(sizeof(Pilha));
    pilha->primeiro == NULL; 
    return pilha; 
}

//Função para inserir em uma pilha dinamica
void pilha_push(Pilha* pilha, float v){
    Lista* novo = malloc(sizeof(Lista)); 
    novo->valor = v;
    novo->prox = pilha->primeiro;
    pilha->primeiro = novo; 
}

float pilha_pop(Pilha* pilha){
    Lista* p;
    float v; 
    if(pilha->primeiro == NULL){
        printf("A pilha está vazia!");
        return;
    }
    p = pilha->primeiro;
    v = p->valor; 
    pilha->primeiro = pilha->primeiro->prox;
    free(p);
    return v; 
}