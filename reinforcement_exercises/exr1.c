// 1) Objetivo: Criar um programa que calcula a média de notas de um aluno, mas o tamanho da quantidade de notas deve ser definido pelo usuário em tempo de execução.


// Escreva um programa em C que faça o seguinte:
// Pergunte ao usuário quantas notas ele deseja digitar (ex: 3, 5, 10).
// Crie um  ponteiro e use alocação dinâmica para criar um vetor do tamanho exato informado pelo usuário.
// Use um laço (for) para ler as notas informadas pelo usuário e guardá-las nesse vetor alocado.
// Calcule e exiba a média aritmética dessas notas.
//  Libere a memória alocada antes de encerrar o programa usando a função apropriada.
// DICA: implemente sem alocação dinâmica. Fixe um tamanho para o vetor. Depois implemente a versão com alocação dinâmica descrita acima. 
// Modifique o programa de cálculo de média de notas para que ele utilize funções específicas. Seu código deve conter obrigatoriamente:
//  Função alcocar_vetor: Recebe a quantidade de notas N, aloca dinamicamente o vetor de float na memória e retorna o ponteiro para a função principal (main).
//  Função calcular_media: Recebe o ponteiro do vetor e a quantidade de notas N. Ela deve percorrer o vetor, calcular e retornar a média  aritmética.
//  Função main: Deve gerenciar a leitura de N, chamar as funções criadas, realizar a leitura das notas digitadas pelo usuário e, obrigatoriamente, fazer a liberação da memória no final.

# include <stdio.h>
# include <stdlib.h>

//Essa função recebe como parametro um numero inteiro que sera usado para alocar dinâmicamente N espaços na memória
float *alocar_vetor(int N){
    int i;
//Aqui, o ponteiro vetor (do tipo float) recebe o primeiro endereço de memória de uma sequência contígua que foi alocada usando calloc.
//Note que o calloc recebe a quantidade de espaços necessários e o tamanho (em bytes) de cada elemento (no caso o tamanho em bytes do float). 
//Por baixo dos panos ele multiplica o tamnho de cada elemento pelo o número de elementos apra reservar os endereços de memória contíguos 
// O (float*) converte o void* padrao do calloc
    float *vetor = (float*) calloc(N, sizeof(float)); 

//Se a alocação der errada, o calloc retorna NULL, então aqui eu verifico se a alocação deu certo.
    if(vetor == NULL){
        printf("Erro na alocação"); 
    }
//Aqui eu preencho os endereços de memória (vetor) com as notas
    for(i=0; i<N; i++){
        printf("Digite a nota %dº: ", i + 1); 
        scanf("%f", &vetor[i]); //Aqui é a mesma coisa de passar (vetor + i)
    }

    return vetor; //retorno o vetor, ou seja, o endereço de memória do meu primeiro "lote"

}
//Essa função recebe o endereço de memoria na onde começa o vetor e a quantidade de elementos
float calcular_media(float *vetor, int N){
    float  soma=0.0; 
    int i;
    //Aqui, uso o for para somar todos os elementos do vetor
    for(i=0; i<N; i++){
        soma += *(vetor+i); //Isso é a mesma coisa que escrever vetor[i], mas usando a notação de ponteiros
    }
    return soma/N; //retorna a media dividindo a soma pela quantidade de elementos
}


int main (){
    int N=0;
    float media = 0.0;
    float *notas;

    printf("Qunatas notas deseja digitar? ");
    scanf("%d", &N); 
    notas = alocar_vetor(N); //notas recebe o primeiro endereço alocado
    media = calcular_media(notas, N); //media recebe o valor da media calculada 
    printf("A media é: %f", media); 
    free(notas); //aqui, libero os endereços de memória alocados na HEAP da memória RAM 
    notas = NULL; //Torno nulo o conteudo de notas (para de apontar)

    return 0;
}
