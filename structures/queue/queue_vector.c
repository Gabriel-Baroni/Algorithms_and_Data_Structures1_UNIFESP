#include <stdio.h>
#include <stdlib.h>
#include "interfaces/queue.h"

#define MAX 10

//Estrutura padrão de fila com vetor
typedef struct fila{
    int qtd;
    int ini;
    int fim; 
    int* dados;
}Fila; 

//Inicializa a fila e seus campos
Fila* criar(){
    Fila* f = malloc(sizeof(Fila));
    f->qtd = 0;
    f->ini = 0;
    f->fim = 0;
    f->dados = malloc(MAX * sizeof(int));
    return f; 
}

//Insere um elemento no final da fila
void inserir(Fila* f, int v){
    if(f->qtd == MAX){
        printf("Fila está cheia");
        exit(1);
    }
    f->fim = (f->ini + f->qtd) % MAX; //O uso do mod é necessário para conseguir usar o vetor com o mecanismo circular
    f->dados[f->fim] = v; 
    f->qtd ++;  
}

//Retira um elemento do início da fila
int retira(Fila* f){
    if(f->qtd == 0){
        prtinf("Fila está vazia");
        exit(1);
    }
    int v = f->dados[f->ini];
    f->ini = (f->ini + 1) % MAX; // O uso do mod é necessário para conseguir usar o vetor com o mecanismo circular 
}

//Libera o vetor de dados e a estrutura fila
void liberar(Fila* f){
    free(f->dados);
    free(f);
}
