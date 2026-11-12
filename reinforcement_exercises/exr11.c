#include <stdio.h>
#include <stdlib.h>

typedef struct arv{
    int info;
    struct arv* esq;
    struct arv* dir; 
}Arv; 

Arv* criar(){
    return NULL;
}
//Função para inserir elementos em uma árvore de busca binária
Arv* inserir(Arv* raiz, int v){
    //Se a raiz é nula, ela começa a apontar para o endereço de memória do novo elemento 
    if(raiz == NULL){
        raiz = malloc(sizeof(Arv));
        raiz->info = v;
        raiz->esq = NULL;
        raiz->dir = NULL;
    //Se o elemento a ser inserido for menor que o conteúdo do endereço de memória que a raiz aponta, o filho esquerdo desse endereço recebe o retorno da chamada recursiva
    } else if(raiz->info > v){
        raiz->esq = inserir(raiz->esq, v);
    } else{
        //Se o elemento a ser inserido for maior que o conteúdo do endereço de memória que a raiz aponta, o filho direito desse endereço recebe o retorno da chamada recursiva
        raiz->dir = inserir(raiz->dir, v); 
    }
    //Retorna o endereço que a raiz deve passar a apontar
    return raiz; 
}

//Função para imprimir os nós da árvore em ordem crescente, ou seja, por ser uma árvore de busca binária, em ordem. 
void imprimir(Arv* raiz){
    if(raiz == NULL){
        return;
    }
    imprimir(raiz->esq);
    printf("%d ", raiz->info);
    imprimir(raiz->dir); 
}

//Função para remover um elemento da árvore 
Arv* remover(Arv* raiz, int v){
    //Verifica se a árvore é vazia
    if(raiz==NULL){
        return NULL;
    }
    //Verifica se o valor a ser removido está na SAE
    if(raiz->info > v){
        raiz->esq = remover(raiz->esq, v);
    //Verifica se o valor a ser removido está na SAD
    } else if(raiz->info < v){
        raiz->dir = remover(raiz->dir, v);
    //Se não está em nenhuma das subarvores, o valor da raiz é o proprio valor a ser removido  
    }else{
        //CASO 1: A raiz não tem filhos
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL; 
        //CASO 2: A raiz tem 1 único filho
        } else if(raiz->esq == NULL){
            Arv* t = raiz;
            raiz = raiz->dir;
            free(t);
        } else if(raiz->dir == NULL){
            Arv* t = raiz;
            raiz = raiz->esq;
            free(t);
        //CASO 3: A raiz tem 2 filhos
        }else{
            Arv* t = raiz->dir;
            while(t->esq != NULL){
                t = t->esq;
            }
            raiz->info = t->info;
            raiz->dir = remover(raiz->dir, t->info); 
        }
    }
    return raiz; 
}

//Função de busca em árvore de busca binário de forma iterativa
Arv* busca(Arv* raiz, int v){
    //Verifica se a árvore é vazia 
    if(raiz == NULL){
        return NULL;
    }
    //Uso um ponteiro do tipo Arv auxiliar e faço ele apontar para o mesmo endereço da raiz
    Arv* t = raiz;
    //Enquanto esse auxiliar for diferente de NULL e o valor do conteúdo do endereço por ele apontado for diferente do valor da buca, faço ele percorrer a árvore
    while(t != NULL && t->info != v){
        if(t->info > v){
            t = t->esq;
        } else if(t->info < v){
            t = t->dir;
        }
    }
    //Retorno o valor encontrado, seja ele um nó ou NULL se nada foi encontrado
    return t; 
}

int main(){
    int lista[] = {10, 22, 26, 2, 11, 1, 5, 23, 24}; 
    //Inicializo a árvore
    Arv* arvore = criar();
    //Preecho a árvore com os valores
    for(int i=0; i<9; i++){
        arvore = inserir(arvore, lista[i]);
    }
    //Imprimo a árvore em ordem
    imprimir(arvore); 
    int lista_remover[] = {1, 2, 10, 25};

    //Excluo esses valores da árvore
    for(int i=0; i<4; i++){
        arvore = remover(arvore, lista_remover[i]);
    }
    //Imprimo a árvore novamente
    printf("\n"); 
    imprimir(arvore); 

    return 0; 
}