#include <stdio.h>
#include <stdlib.h>
#include "interfaces/linearList.h"

#define MAX 10

//Estrutura padrao de lista linear com vetor
typedef struct lista{
    int qtd;
    int* dados;
}Lista; 

Lista* criar(){
    Lista* l = malloc(sizeof(Lista)); //Aloca a estrutura da lista
    l->qtd = 0;
    l->dados = malloc(MAX * sizeof(int)); //Aloca um vetor de inteiros
    return l; 
}

Lista* inserir(Lista* l, int v, int pos){
    if(l->qtd == MAX){ //Verifica se a lista está cheia
        printf("Lista cheia"); 
        return l; 
    }
    if(pos< 0 || pos > l->qtd){ //Verifica se a posição especificada é adequada
        printf("Posição inválida"); 
        return l; 
    }
    for(int i = l->qtd-1; i>=pos; i--){
        l->dados[i+1] = l->dados[i];
    }
    l->dados[pos] = v; 
    l->qtd++;
    return l; 
}


int buscar(Lista*l, int valor){ //Percorre a lista em busca da primeira ocorrência do valor
    for(int i=0; i<l->qtd; i++){
        if(l->dados[i] == valor){
            printf("valor %d encontrado", valor);
            return 1; 
        } 
    }
    return 0; 
}

Lista* remover (Lista* l, int valor){
    if(l->qtd == 0){ //Verifica se a lista esta vazia
        printf("Lisat vazia");
        return l; 
    }
    for(int i=0; i<l->qtd; i++){ //Percorre a lista em busca da primeira ocorrência do valor
        if(l->dados[i] == valor){
            for(int j = i; j<l->qtd-1; j--){ //Desloca todos os valores a partir da posição do elemento encontrado, para a direita
                l->dados[j] = l->dados[j+1];
            }
            l->qtd--;
            return l; 
        }
    }
    printf("Valor não encontrado"); 
    return l; 
}

void liberar(Lista* l){ //Libera a estrutura 
    free(l->dados);
    free(l);
}