#include <stdio.h>
#include <stdlib.h>
#include "interfaces/stack.h"

#define MAX 10

//Estrutura padrão de pilha com vetor
typedef struct pilha{
    int qtd;
    int* dados;
}Pilha;

//Inicializa a pilha e seus campos
Pilha* criar(){
    Pilha* p = malloc(sizeof(Pilha));
    p->qtd = 0;
    p->dados = malloc(MAX*sizeof(int)); 
}

//Insere um elemento no topo da pilha (final do vetor); 
void push(Pilha* p, int v){

    if(p->qtd == MAX){
        printf("Lista esta cheia");
        exit(1);
    }

    p->dados[p->qtd] = v;
    p->qtd++;
}

//Retira um elemnto do topo da pilha (final do vetor)
int pop(Pilha*p){
    if(p->qtd == 0){
        printf("Pilha vazia");
        exit(1);
    }
    int v = p->dados[p->qtd--];
    p->qtd--; 
    return v; 
}

//Libera o vetor e a estrutura da pilha
void liberar(Pilha* p){
    free(p->dados);
    free(p);
}
