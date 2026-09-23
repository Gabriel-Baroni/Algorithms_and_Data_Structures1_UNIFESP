// Implemente as funções de inserção, busca e remoção para lista circular duplamente encadeada.
#include <stdio.h>
#include <stdlib.h>

 typedef struct lista{
    int info;
    struct lista* prox; 
    struct lista* ant;
 }Lista; 

 Lista* inserir(Lista*l, int v){
    Lista* novo = malloc(sizeof(Lista));
    novo->info = v;
    if(l == NULL){
        novo->prox = novo;
        novo->ant = novo;
        return novo;
    }
    novo->prox = l;
    novo->ant = l->ant;
    l->ant->prox = novo;
    l->ant  = novo;
    return novo;  
 }

 Lista* busca (Lista* l, int v){
   Lista* p = l;

   if(p==NULL){
      printf("Lista vazia");
      return NULL;
   }

   do{
      if(p->info == v){
         return p;
      }
      p = p->prox;
   }while(p!=l); 

   printf("Item não encontrado");
   return NULL; 
 }

 Lista* retira (Lista* l, int v){
   Lista* p = l;
   if(p==NULL){
      printf("Lista vazia");
      return l;
   }
   if(p->info ==v && p->prox == p){
      free(p);
      return NULL;
   }

   if(p->info ==v && p == l){
      p->ant->prox = p->prox; 
      p->prox->ant = p->ant; 
      l = p->prox;
      free(p);
      return l; 
   }

   do{
      if(p->info == v){
         p->ant->prox = p->prox; 
         p->prox->ant = p->ant; 
         free(p); 
         return l; 
      }
      p= p->prox; 
      
   }while(p!=l);

   printf("Item não encontrado");
   return l; 
 }

 