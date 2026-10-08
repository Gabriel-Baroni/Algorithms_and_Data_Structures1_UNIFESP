//Implemente um fila estática e suas operações com mecanismo circular.

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct fila{
    int ini; //indicice do início
    int fim; //indice do fim
    int vet[MAX]; //Vetor estático para guardar os elementos
    int n; //Número de elementos na fila
}Fila;

//Função para criar uma estrutura Fila e incializar os seus campos
Fila* criar(){
    Fila* f = malloc(sizeof(Fila));
    f->n = 0;
    f->ini = 0;
    f->fim = 0;
    return f;
}
//Função para verificar se a fila está vazia (retorno booleano)
int verificar_vazia(Fila* f){
    return (f->n==0);
}

//Função para inserir um novo elemento no fim da fila
void inserir (Fila* f, int v){
    if(f->n == MAX){ //Verifica se a fila esta cheia
        printf("A fila está cheia");
        return;
    }
    f->fim = (f->ini + f->n) % MAX; //Arruma o indice para o fim da fila
    f->vet[f->fim] = v; //Atribui o valor no fim da fila 
    f->n++; //Incrementa o número de elementos
}

//Função para retirar um elemento do início da fila 
int retirar (Fila* f){
    int v; //Variável auxiliar para armazenar o valor a ser retirado
    if(verificar_vazia(f)){ //Verifica se a fila está vazia
        prtinf("Fila esta vazia");
        return;
    }
    v = f->vet[f->ini]; //Pega o valor do primeiro da fila
    f->ini = (f->ini++)% MAX; //Ajusta o indice do primeiro para ser o próximo
    f-> n--; //Diminui o número de elementos 
    return v;  //Retorna o valor em questão 
}

//Libera a estrutura alocada 
void liberar(Fila* f){
    free(f);
}