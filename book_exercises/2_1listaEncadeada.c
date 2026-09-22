#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista* prox; 
}Lista;

Lista* criar(void){
    return NULL; 
}

int comprimento (Lista* l){
    int cont = 0;
    Lista* p; 
    for(p=l; p != NULL; p=p->prox){
        printf("%d ", p->info); 
        cont++;
    }
    return cont; 

}

void insere(Lista** l, int v){
    Lista* novo = malloc(sizeof(Lista));
    novo->info = v;
    novo->prox = *l;
    *l = novo; 
}

void limpa(Lista* l){
    Lista* p;
    for(p=l; p!=NULL; p=p->prox){
        Lista* t = p->prox;
        free(p);
        p = t; 
    }
}


int main (){
    Lista* l = criar(); 
    insere(&l, 10);
    insere(&l, 8);
    insere(&l, 100);
    insere(&l, 100);
    insere(&l, 8);
    printf("A lista simplesmente encadeada tem: %d", comprimento(l));    
}