#include <stdio.h>
#include <stdlib.h>

typedef struct No {
int simbolo; // simbolo armazenado no noh
struct No *prox; // ponteiro para o proximo noh
struct No *ant;// ponteiro para o noh anterior
}No;

typedef struct Tambor {
No *cabeca; // ponteiro para a cabeca da sequencia de simbolos
}Tambor;

typedef struct Maquina{
int n_tambores; // numero de tambores na maquina
Tambor *tambores; // ponteiro para VETOR de Tambor e NAO vetor de PONTEIROS de Tambor
}Maquina;

// cria_maquina: recebe um número de tambores, aloca uma máquina e inicializa o campo “cabeca”;
Maquina* cria_maquina(int n_tambores){
    Maquina* maquina = malloc(sizeof(Maquina)); //Cria um ponteiro do tipo maquina que aponta para uma maquina alocada dinamicamente
    maquina->n_tambores = n_tambores; //Atribui no campo n_tambores da maquina o numero passado como parametro na função
    maquina->tambores = malloc(n_tambores*sizeof(Tambor)); //atribui no campo tambores da maquina o endereço de memoria que do primeiro tambor em um espaço contíguo de n tambores alocados dinamicamente
    //Loop para inicializar com NULL a cabeca de cada tambor
    for(int i = 0; i< n_tambores; i++){
        maquina->tambores[i].cabeca = NULL;  
    }
    return maquina; //Retorna o endereço da maquina para a main

}
// insere_simbolo: recebe a referência de um “Tambor” e um símbolo, insere o símbolo no tambor sem retornar nada;
void insere_simbolo (Tambor* tambor, int simbolo){
    No* novo_simbolo = malloc(sizeof(No)); //Aloca um novo nó (simbolo) da lista duplamente encadeada circular e atribui seu endereço a um ponteiro do tipo no
    novo_simbolo->simbolo = simbolo;  //Attribui ao campo simbolo desse novo nó o valor passado pelo parametro da função

    if(tambor->cabeca == NULL){//Verifica se a lista está vazia
        novo_simbolo->prox = novo_simbolo; //Faz o proximo do elemento ser ele mesmo
        novo_simbolo->ant = novo_simbolo; //Faz o anterior do elemento ser ele mesmo
        tambor->cabeca = novo_simbolo; //Faz a cabeça apontar para o novo elemento
    } else{ //Se a lista não está vazia
        novo_simbolo->prox = tambor->cabeca; //O campo proximo do novo elemento recebe o que a cabeça estava apontando
        novo_simbolo->ant = tambor->cabeca->ant; //O campo anterior do novo elemento recebe o anterior da cabeça
        tambor->cabeca->ant->prox = novo_simbolo; //O capo próximo do anterior da cabeça recebe o novo elemento
        tambor->cabeca->ant = novo_simbolo; // O campo anterior da cabeça recebe o novo elemento
    }
}
// remove_simbolo: recebe a referência de um “Tambor” e um símbolo, remove o símbolo 
// do tambor (se o símbolo pertencer ao tambor) e não retorna nada;

void remove_simbolo(Tambor* tambor, int simbolo){
    No* p = tambor->cabeca; //Cria um ponteiro do tipo nó e faz ele apontar para onde a cabeça esta apontando
    if(p!=NULL && p->simbolo == simbolo && p->prox == p){ //Verifica se é o primeiro e único elemento da lista
        free(p); //Desaloca esse elemento
        tambor->cabeca = NULL; //Faz a lista aponrtar para NULL (lista vazia)
        return;

    }

    if(p!=NULL && p->simbolo == simbolo && p==tambor->cabeca){ //Verifica se é o primeiro, mas não o único elemento da lista
        p->prox->ant = p->ant; //O campo anterior do proximo elemento do ponteiro p passsa a apontar para o anterior de p
        p->ant->prox = p->prox; // O campo proximo do anterior do elemento p passa a apontar para o proximo de p
        tambor->cabeca = p->prox; // A cabeça passa a apontar para o proximo de p
        free(p); //Desaloca o p
        return;

    }
    do{ //Uso o loop "do... while" por ser um lista duplamente encadeada circular
        if(p!=NULL && p->simbolo == simbolo){ 
            p->prox->ant = p->ant; //O campo anterior do proximo elemento de p passa a apontar para o anterior de p
            p->ant->prox = p->prox; // O campo proximo do anterior elemento de  p passa a apontar para o proximo de p
            free(p); //Desaloca o p
            return;
        }
        p = p->prox; //Passa para o proximo elemento
    }while(p!= tambor->cabeca); //Faz isso ate chegar novamente para onde a cabeça aponta
}

// desaloca_tambor: recebe a referência de um “Tambor” e desaloca essa tambor;
void desaloca_tambor(Tambor* tambor){
    No* p = tambor->cabeca; //Cria um ponteiro tipo no e faz ele apontar para onde a cabeça aponta
    do{
        No* t = p->prox; //Cria um ponteiro auxiliar e atribui a ele o endereço do proximo elemento de p
        free(p); //Desaloca p
        p= t; 
    }while(p!= tambor->cabeca);
    tambor->cabeca = NULL; //Faz a cabeça apontar para NULL (não tem mais nenhum no)
}

// desaloca_caixas: recebe uma referência de “Maquina”, invoca a função “desaloca_tambor”
// e desaloca os tambores; 
void desaloca_caixas(Maquina* maquina){
    //Loop para percorrer o vetor de tambores da maquina
    for(int i =0; i<maquina->n_tambores; i++){
        desaloca_tambor(&maquina->tambores[i]); //Passa o endereço de memoria do tambor i da maquina 
    }
    free(maquina->tambores);//Libera o vetor de tambores
}

//Função que recebe a referencia da maquina, o numero de tambores e vetores auxiliares para realizar a rotação dos tambores
void girar_tambores(Maquina* maquina, int n, int* vetor_rotacoes, int* vetor_sentido){
    //Loop duplo para fazer a rotação de cada tambor da maquina
    for(int i=0; i<n; i++){ //Faz o loop "vezes", ou seja, o numero de tambores
        No* p = maquina->tambores[i].cabeca; //Cria um ponteiro do tipo no para apontar para a cabeça do tambor atual
        for(int j=0; j<vetor_rotacoes[i]; j++){ //Faz o loop a quantidade de vezes de rotações passadas através do vetor rotações
            if(vetor_sentido[i] == 0){ //Se o sentido de rotação for igual a zero, a lista é lida pela direita
                p = p->prox;
            } else { //Se não é lida pela esquerda
                p= p ->ant; 
            }
        }
        //Imprime adequadamente os valores da rotação
        if(i==0){
            printf("-%d-", p->simbolo);
        } else{
            printf("%d-", p->simbolo);
        }
    }
}

int main(){
    int n, m; //Respectivamente, numero de tambores, numero de elementos em cada tambor 
    //Vetores auxiliares
    int* vetor_rotacoes;
    int* vetor_sentido; 
    int* vetor_remocoes;
    //Input dos valores de n e m 
    scanf("%d", &n);
    scanf("%d", &m); 
    //Alocação dinamica dos vetores auxiliares 
    vetor_rotacoes = malloc(n*sizeof(int));
    vetor_sentido = malloc(n*sizeof(int)); 
    vetor_remocoes = malloc(n*sizeof(int)); 
    //Cria a maquina
    Maquina* maquina = cria_maquina(n); 
    //Loop duplo para inserir os valores em cada tambor
    for(int i=0; i<n; i++){ //Repete o loop "n" vezes, ou seja, a qunatidade de tambores
        for(int j=0; j<m; j++){//Repete o loop "m" vezes, ou seja, a quantidade de elementos por tambor
            int k = 0; 
            scanf("%d", &k); //Input do valor a ser inserido
            insere_simbolo(&maquina->tambores[i], k); //Chamada da fuinção de inserir, passando o endereço de memória do tambor i e o valor k 
        }
    }

    //Loop para pegar a quantida de rotação de cada tambor
    for(int i=0; i<n; i++){
        scanf("%d", &vetor_rotacoes[i]); 
    }
    
    //Loop para pegar o sentido de rotação de cada tambor
    for(int i=0; i<n; i++){
        scanf("%d", &vetor_sentido[i]); 
    }

    //Loop para pegar os valores a serem removidos
    for(int i=0; i<n; i++){
        scanf("%d", &vetor_remocoes[i]); 
    }

    //Gira a maquina pela primeira vez
    girar_tambores(maquina, n, vetor_rotacoes, vetor_sentido); 
    printf("\n"); 

    //Loop para remover os simbolos de cada tambor
    for(int i= 0; i<n; i++){
        remove_simbolo(&maquina->tambores[i], vetor_remocoes[i]); //Passa o endereço de memoria do tambor i
    }

    //Gira a maquina pela segunda vez
    girar_tambores(maquina, n, vetor_rotacoes, vetor_sentido); 
    //Desaloca os tambores
    desaloca_caixas(maquina);
    //Desaloca os vetores auxiliares
    free(vetor_rotacoes);
    free(vetor_sentido); 
    free(vetor_remocoes);
    //Desaloca a maquina
    free(maquina); 

    return 0; 
}