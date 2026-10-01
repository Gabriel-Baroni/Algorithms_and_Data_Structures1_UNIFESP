// 1) Implemente uma pilha estática e suas operações.
#include <stdio.h>
#include<stdlib.h>
#define MAX 50

//Estrutura padrao de uma pilha estática
typedef struct pilha{
    int n;
    float vet[MAX];
}Pilha; 

//Função para criar uma pilha estática
Pilha* cria(){
    Pilha* pilha = malloc(sizeof(Pilha));
    pilha->n = 0;
    return pilha; 
}

//Função para inserir em uma pilha estática (push)
void pilha_push(Pilha* pilha, float v){
    if(pilha->n == MAX){
        printf("Pilha está cheia!");
        return; 
    }
    pilha->vet[pilha->n] = v;
    pilha->n++;
}

//Função para remover em uma pilha estática (pop)
float pilha_pop(Pilha* pilha){
    float v;
    if(pilha->n == 0){
        printf("Pilha vazia!");
        return;
    }
    v= pilha->vet[pilha->n-1];
    pilha->n--;
}

//Função para verificar se a pilha está vazia
int pilha_vazia(Pilha* pilha){
    if(pilha->n==0){
        return 1;
    } else{
        return 0; 
    }
    //posso subistuir isso tudo apenas por "return (pilha->n == 0)"
}

// Função para desalocar a pilha
void liberar(Pilha* pilha){
    free(pilha);
}

