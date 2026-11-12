#include <stdio.h>
#include <stdlib.h>

//Estrutura de um nó de árvore de busca binária
typedef struct no{
    int info;
    struct no* esq;
    struct no* dir; 
}No;

//Função para criar uma árvore vazia
No* cria_vazia(){
    return NULL;
}

//Supondo que a gente tenha uma árvore já criada e ordenada, temos essas funções para realizar sobre a essa árvore

//Função para realizar uma busca binária na árvore
No* buscar(No* raiz, int v){
    //Se raiz estiver vazia a árvore está vazia, não retorna nada
    if(raiz == NULL){
        return NULL;
    }
    //Se o valor da raiz for igual ao valor a ser procurado, retonra essa raiz
    if(raiz->info == v){
        return raiz;
    //Se o valor da raiz for maior que o valor a ser produrado, chama a função passando o filho da esquerda
    } else if(raiz->info > v){
        return buscar(raiz->esq, v);
    //Se não, vai chamar a função com o filho da direita
    } else {
        return buscar(raiz->dir, v); 
    }
}

No* inserir(No* raiz, int v){
    //Se a raiz for igual a NULL, quer dizer que a árvore esta vazia, isso significa que o novo elemento será a própria raiz
    if(raiz == NULL){
        raiz = malloc(sizeof(No));
        raiz->info = v;
        raiz->esq = NULL;
        raiz-> dir = NULL;
    //Se a raiz for maior que o valor a ser inserido, chama a função de inserir passando o filho da esquerda
    } else if(raiz->info > v){
        raiz->esq = inserir(raiz->esq, v);
    } else{
    //Se não chama a função recursivamente passando o filho da direita
        raiz->dir =  inserir(raiz->dir, v); 
    }
    return raiz; 
}

No* remover(No* raiz, int v){
    //Se a arvore esta vazia, retorna NULL, não tem o que remover
    if(raiz==NULL){
        return NULL;
    }
    //Se o valor a ser removido for menor que a raiz, o filho da esquerda da raiz recebe o retorno da chamada recursiva passando o filho da esquerda
    if(raiz->info > v){
        raiz->esq = remover(raiz->esq, v);
    //Se o valor a ser removido for maior que a raiz, o filho da direita da raiz recebe o retorno da chamada recursiva passando o filho da direita
    } else if (raiz->info < v){
        raiz->dir = remover(raiz->dir, v);
    } else{
        //CASO 1: A o nó a ser removido é uma folha (não tem filhos)
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        //CASO 2: O nó a ser removido tem algum filho, ou na esquerda, ou na direita
        } else if (raiz->esq ==NULL){
            No* t = raiz->dir;
            free(raiz);
            return t;  
        } else if (raiz->dir == NULL){
            No* t = raiz->esq;
            free (raiz);
            return t; 
        //CASO 3: O nó a ser removido tem 2 filhos 
        } else {
            //Faço um ponetiro auxiliar receber o valor do filho da direita da raiz
            No* t = raiz->dir; 
            //Faço esse ponteiro percorrer até achar o elemento mais a esquerda da SAD da raiz (o sucessor da raiz)
            while(t->esq != NULL){
                t = t->esq;
            }
            //Coloco a informação desse elemento encontrado na raiz
            raiz->info = t->info; 
            //Chamo a função de remover passando o elemento encontrado como valor a ser retirado 
            raiz->dir = remover(raiz->dir, t->info); 
        }
    }
    return raiz; 
}