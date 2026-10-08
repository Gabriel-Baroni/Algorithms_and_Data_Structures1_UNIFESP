//Implemente uma fila dinâmica e suas operações
#include <stdlib.h>
#include <stdio.h>

//Estrutura padrao de uma Nó de uma lista simplemeste encadeada
typedef struct lista{
    int info;
    struct lista* prox;
}No;

//Estrutura padrão de uma Fila dinâmica
typedef struct fila{
    No* ini;
    No* fim;
}Fila;

//Função para criar uma fila e inicializar seus campos
Fila* criar(){
    Fila* f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL; 
    return f; 
}

//Função para inserir um elemento no final da fila
void inserir (Fila* f, int v){
    No* novo = malloc(sizeof(No)); //Aloca um novo nó
    novo->info = v; //Atribui o valor ao campo do novo nó
    novo->prox = NULL; //Como o novo nó será o último elemento, o prox dele é NULL
    if(f->fim != NULL){ //Se a fila não estiver vazia
        f->fim->prox = novo; //O próximo do antigo último é o novo nó
    } else {
        f->ini = novo; //Se a fila esta vazia, então o novo nó é o primeiro da fila
    }
    f->fim = novo; //O fim da fila é o novo nó 
}

//Função para remover um elemento do início da fila
int remover (Fila* f){
    No* removido;
    int v;
    if(f->ini == NULL){ //Verifica se a lista esta vazia
        printf("A lista está vazia");
        return;
    }
    removido = f->ini; 
    f->ini = removido->prox; 
    if(f->ini == NULL){ //Se depois de ajustar os ponteiros, alista ficou vazia
        f->fim = NULL; //Significa que o ini e o fim estao vazios, pois a lista esta vazia
    }
    v = removido->info;
    free(removido); // Remove o nó em qeustão
    return v; //Retorna o valor que ele armazenava 
}
//Função para liberar todos os nós da fila e a própria fila
void liberar(Fila* f){
    No* v = f->ini;
    while(v != NULL){
        No* t = v->prox;
        free(v);
        v = t; 
    }
    free(f); 
}