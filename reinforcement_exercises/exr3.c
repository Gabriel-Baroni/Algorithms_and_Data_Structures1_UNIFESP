//  2) Implemente uma função para inserção em uma lista linear dinâmica (com encadeamento) de forma que seja possível inserir 
//  um elemento após um outro elemento que já está na lista.
 
 #include <stdio.h>
 #include <stdlib.h>

//Faço a estrutura de nó da lista encadeada
typedef struct no{
    int info;
    struct no* prox; 

}lista; //Com o typedef, dou o nome de lista

//Inicializo a lista com o endereço NULL 
lista* inicializa(){
    return NULL;
}

//Função para inserir elementos no inicio da lista
lista* insere_inicio(lista* l, int i){
    lista* novo = (lista*) malloc(sizeof(lista)); //Aloco dinamicamente um espaço para um nó
    novo->info = i; //Atribuo ao campo info desse nó o valor passado 
    novo->prox = l; //faço o campo prox desse nó apontar para onde a cabeça da lista estava apontando
    return novo; //retorno o novo nóo (endereço dele), assim, a cabeça vai apontar para ele
}
//Função para inserir elementos após um determinado indice da lista
lista* insere_apos(lista* l, int i, int v){
    lista* p = l;  // Variável auxiliar que vai ajudar a percorrer a lista
    int c = 0; //Contador para saber se chegamos no indice falaso
    while(p!=NULL && c<i){ 
        p= p->prox; // a variavel p passa para o proximo nó
        c++; // o contador incrementa
    }

    if(p!=NULL){ 
        lista* novo = (lista*) malloc(sizeof(lista)); //aloco dinamicamente um espaço para o tamanho de um nó
        novo->info = v; //esse novo  nó recebe no seu campo info o valor passado 
        novo->prox = p->prox; // o novo nó vai apontar para onde o p estava apontando
        p->prox = novo;  //o p vai apontar o novo nó
        printf("Valor %d inserido com sucesso apos o indice %d.\n", v, i);
    } else {
        // Se p ficou NULL, a lista acabou antes de chegar no índice
    printf("Erro: O indice %d e maior que o tamanho da lista.\n", i);
    }
    return l; //retorno l para não perder a referencia
}
void imprimir(lista* l){
    lista* p; //Variavel auxiliar para percorrer toda a lista
    for(p=l; p!=NULL; p=p->prox){ // começa onde a cabeçça aponta e vai percorrendo os nós até chegar em NULL 
        printf("%d; ", p->info); 
    }
}

void liberar(lista* l){
    lista* p =l;
    while(p!=NULL){ //Libera do começo para o final 
        lista* t = p->prox; 
        free(p);
        p = t; 
    }
}

int main(){
    lista* l; //Cabeça da lista encadeada
    l = inicializa(); 
    l = insere_inicio(l, 2);
    l = insere_inicio(l, 1);
    l = insere_apos(l, 0, 10);
    imprimir(l);
    liberar(l); 
    return 0;
}