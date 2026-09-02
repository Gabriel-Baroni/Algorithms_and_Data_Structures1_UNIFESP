// Implemente uma função para inserção em uma lista linear estática (com vetor) de forma que seja possível inserir 
// um elemento em uma posição específica.

#include <stdio.h>
#include <stdlib.h>

typedef struct{ //Crio a minha estrutura de dados base (Lista linear Estática)
    int max; //Quantidade máxima que a minha lista linear estática pode ter
    int qtd; //Quantidade atual que a minha lista linear estática tem
    int* dados; //Ponteiro para o alocamento onde os elementos são armazenados de forma contígua    
}Lista;

Lista* inicializa(int max){ //Essa função inicializa a minha estrutura, alocando dinamicamente a memória para a minha estrutura e definindo os valores inciais de seus campos
    Lista* l; //Cria um ponteiro do tipo Lista (minha estrutura)
    l = malloc(sizeof(Lista)); //Aloca um espaço na memória para o tamanho do meu tipo lista e passa o endereço para o meu ponteiro
    l -> max = max; //Atribui ao campo max o máximo de elementos definidos via terminal
    l -> qtd = 0; //Inicializa a quantidade de elementos com zero
    l -> dados = malloc(max*sizeof(int)); //Aloca dinamicamente o espaço para o vetor dados (para o máximo de elementos definidos)
    return l; //Retorna o ponteiro para a minha estrutura
}

int insere (Lista* l, int i, int pos){ //Essa função permite inserir um dado em qualquer posição da lista linear estática
    int j;
    if(l->qtd < l->max){ //Verifico se a lista já esta cheia
        for(j=l->qtd -1; j>=pos-1; j--){ //Empurro todos os elementos que estão a direita da posiçãoq que quero inserir
            l->dados[j+1] = l->dados[j];  
        }
        l->dados[pos-1] = i; //Quando chego na posição desejada, o loop acaba e eu aatribuo valor para a posição
        l->qtd++; //Incremento a quantidade de elementos da lista
        return 1; 
    } 
    return 0; 
}



int main(){
    Lista* l; //Crio um ponteiro do tipo lista
    int tam; 
    printf("Digite o tamanho máximo para a lista linear estática: ");
    scanf("%d", &tam);
    l = inicializa(tam); //Inicializo a minha estrutura com o tamanho que eu falei
    insere(l, 1, 1); //Insiro 1 na primeira posição
    insere(l, 3, 2); //Insiro 3 na segunda posição
    insere(l, 2, 2); //Insiro 2 na segunda posição e 3 passa a estar na terceira posição
    for(int i =0; i<l->qtd; i++){ //Faco um loop for para imprimir os valores
        printf("%d ", l->dados[i]); 
    }
    free(l->dados);
    free(l); 
    return 0;
}