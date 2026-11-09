/******************************************************************************
 * Nome: Gabriel de Paula Baroni
 * RA 193356
 * Disciplina: Algoritmos e Estruturas de Dados 1 (AED I)
 * Laboratorio: 8
 * Descricao: Programa para encontrar um intervalo de valores em uma lista
 *            ordenada utilizando Busca Binaria recursiva.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int busca_binaria(int* l, int x, int n){
    //Condição de parada (Se tem menos que 2 elementos, não tem como ter um par)
    if(n < 2){
        return 0;
    }
    //Divide a quantidade de elementos por 2, usa (n-1) por conta do indice
    int d = (n-1)/2;
    //Se achou o par exato, imprime e retorna 1
    if(x>l[d] && x<l[d+1]){
            printf("%d %d", l[d], l[d+1]); 
            return 1;
    //Se for maior que o elemento do meio mais 1, descarta a metade de inferior
    } else if(x>l[d+1]){
           return busca_binaria(l+d+1, x, n-(d+1));
    } else{
        //Se for menor, descarta a metade superior
        return busca_binaria(l, x, d+1);
    }
}

int main(){
    //Declaração de variáveis e alocação dinâmica 
    int x, n, *lista;
    scanf("%d %d", &x, &n);
    lista = malloc(n*sizeof(int));

    //Percorre a lista a preenchendo
    for(int i = 0; i<n; i++){
        scanf("%d", &lista[i]); 
    }
    //Verifica se retornou 0 ou 1 
    if(!busca_binaria(lista, x, n)){
        printf("nao ha intervalo valido");
    } 

    //Libera a lista
    free(lista); 
}