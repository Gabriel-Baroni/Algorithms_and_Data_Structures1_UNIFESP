// Implemente um programa em C para realizar a transposição de uma matriz M × N.
#include <stdio.h>
#include <stdlib.h>

// Recebe a quantidade de linhas e colunas da matriz, aloca dinamicamente a matriz e
// retorna o ponteiro para a matriz criada.
int * alocar_matriz(int M, int N){ //Essa função retorna um ponteiro de inteiro
    int *matriz; //Decidi por realizar o alocamento de uma matriz pela abstração de um vetor linear (por conta dos requisitos da função liberar_matriz)
    matriz = (int *)malloc(M* N *sizeof(int)); //Utilizando malloc, aloco um espaço para M*N inteiros
    if(matriz == NULL){ //Vefico se o alocamento ocorreu corretamente
        return NULL;
    }
    return matriz; //Retorno o ponteiro que aponta para o primeiro elemento da matriz 
}

// Recebe a matriz original, sua quantidade de linhas e colunas, chama a função
// alocar_matriz para criar a matriz transposta, realiza a transposição e retorna o ponteiro da matriz trans-
// posta.
int * transpor_matriz(int *mat, int M, int N){ //Essa função retorna um ponteiro de inteiro
    int *matrizT, i, j;
    matrizT = alocar_matriz(N, M);  //O ponteiro matrizT recebe o endereço de memoria do primeiro byte alocado pela função alocar_matriz, passei os parametros invertidos, pois serão N linhas e M colunas na tansposta
    for(i=0; i<M; i++){ //Percorre as linhas da matriz normal e as colunas da transposta
        for(j=0; j<N; j++){ //Percorre as colunas da matriz normal e a linnha da trasnposta 
            matrizT[j * M + i] = mat[i * N + j]; // Como utilizei a abstração de vetor linear, não posso usar a lógica de colchetes duplos (matriz[][]). Por isso preciso usar da fórmula (linha * Total de Colunas + coluna). 
        }
    }
    return matrizT; 
}
// Recebe um ponteiro para matriz transposta, suas dimensões e exibe seus elemen-
// tos na tela.
void imprimir_matriz(int *mat, int N, int M){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<M; j++){
            printf("%d ", mat[i * M + j]);  //Utiliza da mesma notação para acessar cada elemento da matrizT e imprimi-lo
        }
        printf("\n"); //Quando sair do laço do incremento da coluna, vai dar um \n 
    }
}
// Recebe uma matriz alocada dinamicamente e a desaloca.
void liberar_matriz(int *mat){
    free(mat); //Libera a alocação apontada pelo ponteiro passado
}

int main(){
    int i, j, M, N, *matriz, *matrizT;
    scanf("%d %d", &M, &N); //Le as dimensoes da matriz
    matriz = alocar_matriz(M, N);  //Aloca um espaço para essa matriz 

    for(i=0; i<M; i++){ //Percorre as minhas da matriz
        for(j=0; j<N; j++){ //Percorre as colunas da matriz
            scanf("%d", &matriz[i* N + j]); //Pega o input do teclado para cada elemento
        }
    }
    
    matrizT = transpor_matriz(matriz, M, N); //Faz a transpotsa

    imprimir_matriz(matrizT, N, M); //Impriem a transposta (note que as dimensões são trocadas)
    //Libera os espaços alocados para as matrizes
    liberar_matriz(matriz);
    liberar_matriz(matrizT);

    return 0;
}