#include <stdio.h>
#include <stdlib.h>

//Estrutura para cada tarefa de impressão (Nó de lista duplamente encadeada)
typedef struct lista{
    int ID;
    int paginas;
    char prioridade;
    struct lista* prox;
    struct lista* ant;
}No;

//Estrutura de uma fila
typedef struct fila{
    No* ini;
    No* fim;
}Fila; 

//Função para alocar um fila e inicializar seus parametros
Fila* criar (){
    Fila* f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f; 
}

//Função para adicionar uma nova tarefa a uma fila de impressão
void adicionar(Fila* f, int ID, int paginas, char prioridade){
    No* novo = malloc(sizeof(No));
    novo->ID = ID;
    novo->paginas = paginas;
    novo->prioridade = prioridade;
    novo->prox = NULL;
    novo->ant = NULL;  
    if(f->fim != NULL){ //Se a fila não for vazia
        f->fim->prox = novo; //Adiciona a nova tarefa no final 
        novo->ant = f->fim;
    } else { //Se a fila for vazia
        f->ini = novo; //Adiciona como primeira tarefa
        novo->ant = NULL;
    }
    f->fim = novo; //O fim passa a apontar para essa nova tarefa
}

//Função para processar/imprimir uma tarefa
No* processar(Fila* f){
    No* tarefa = f->ini;
    if(f->ini == NULL){ //Se a fila estiver vazia, não tem nada para imprimir
        printf(" "); 
        return f->ini;
    }
    f->ini = f->ini->prox;  //O inicio da fila passa a ser a proixima tarefa

    if(f->ini != NULL){ //Se o novo inicio nao for vazio
        f->ini->ant = NULL; //O antecessor dele vai ser  NULL (é o primeiro da fila)
    } else{
        f->fim = NULL; //Se o início estiver vazio, a fila está vazia, assim o fim deve apontar para NULL também
    }
    return tarefa; //Volta o nó da tarefa processada
}

//Função auxiliar para verificar se na fila especiífica tem o ID da tarefa
No* tem_id(Fila* f, int id){
    No* l = f->ini;
    while(l!=NULL){ //Percorre a lista buscando o id
        if(l->ID == id){
            return l; 
        }
        l=l->prox;
    }
    return NULL; 
}

//Função para cancelar uma tarefa 
void cancelar (Fila* f, No* no){
    if(f->ini == no && f->fim == no){ //Se a fila tiver só uma tarefa
        printf("%d %d %c\n", no->ID, no->paginas, no->prioridade); //Imprimo ela
        free(no); //libero a tarefa
        f->ini = NULL; 
        f->fim = NULL;
        return;
    }

    if(f->ini == no && f->fim != no){ //Se a tarefa a ser cancelada for a primiera, mas a fila tem mais tarefas
        printf("%d %d %c\n", no->ID, no->paginas, no->prioridade); //Imprimo a tarefa
        f->ini = no->prox; //O novo início é o próximo elemento
        f->ini->ant = NULL;
        free(no);
        return;
    }

    if(f->ini != no && f->fim == no){ //Se a tarefa a ser cancelada for a última
        printf("%d %d %c\n", no->ID, no->paginas, no->prioridade); //Imprimo ela
        f->fim = no->ant; //O fim passa a ser a tarefa anterior
        f->fim->prox = NULL;
        free(no);
        return;
    }
    //Caso seja uma tarefa que esta no meio da fila
    printf("%d %d %c\n", no->ID, no->paginas, no->prioridade); //Imprimo ela
    no->ant->prox = no->prox; 
    no->prox->ant = no->ant;
    free(no);
}

//Função para exibir a lista de impressao
void exibir (Fila* f, int ordem){
    if(f->ini == NULL){ //Se a fila estpa vazia, retorna
        return; 
    }

    if(ordem == 0){ //Se a ordem for normal
        No* l = f->ini; //Começa a ler a fila da primeira posição (primeira tarefa a ser executada)
        while(l!=NULL){
            printf("%d %d %c\n", l->ID, l->paginas, l->prioridade); 
            l = l->prox; 
        }
    } else {
        No* l = f->fim; //Começa a ler a fila da última posção (última tarefa a ser executada)
        while(l!=NULL){
            printf("%d %d %c\n", l->ID, l->paginas, l->prioridade); 
            l = l->ant; 
        }
    }

}
//Função para desalocar a fila e todos as suas tarefas
void liberar(Fila* f){
    No* l = f->ini;
    while(l!=NULL){ //Percorre a fila desalocando cada tarefa
        No* t = l->prox;
        free(l);
        l = t; 
    }
    free(f); //Desaloca a a própria fila
}

int main(){
    Fila* normais = criar(); //Fila para as tarefas normais
    Fila* urgentes = criar(); //Fila para as tarefas urgentes
    int n;   
    scanf("%d", &n); //Leio o número de operações a serem realizadas
    for(int i=0; i<n; i++){
        char acao;
        scanf(" %c", &acao); //Leio a ação a ser executada
        if(acao == 'P'){
            if(urgentes->ini != NULL){ //Se tiver alguma tarefa na fila de urgentes, a primeira tarefa será processada
                No* tarefa = processar(urgentes);
                printf("%d %d %c\n", tarefa->ID, tarefa->paginas, tarefa->prioridade);
                free(tarefa);
            } else if(normais->ini != NULL){ //Se não tiver tarefas na fila de urgentes, a primeira tarefa da fila de normais será executada
                No* tarefa = processar(normais);
                printf("%d %d %c\n", tarefa->ID, tarefa->paginas, tarefa->prioridade);
                free(tarefa);
            } else{
                printf("\n"); 
            }
        } else if(acao == 'C'){
            int id;
            scanf("%d", &id);
            No* alvo = tem_id(urgentes, id); //Pesquisa na fila de urgentes a existencia do ID
            if(alvo != NULL){ 
                cancelar(urgentes, alvo); //Caso o ID exista na fila de urgentes cancela essa tarefa
            } else{
                alvo = tem_id(normais, id); //Procura pelo ID na fila de normais 
                if(alvo != NULL){
                    cancelar(normais, alvo); //Caso o ID exista na fila de normais, cancela essa tarefa 
                } else{
                    printf("\n"); 
                }
            }
        } else if(acao == 'E'){
            int sentido;
            scanf("%d", &sentido); //Le o sentido desejado 
            if(urgentes->ini != NULL || normais->ini != NULL){ //Se alguma das filas esta com alguma tarefa 
                if(sentido == 0){ //Se o sentido for normal
                    exibir(urgentes, 0); //Primeiro são exibidas as urgentes da primeira para a última tarefa
                    exibir(normais, 0); //Depois são exibidas as normais da primeira para a última tarefa
                } else {//Se a ordem for inversa 
                    exibir(normais, 1); //Primeiro são exibidas as normais da última para a primeira tarefa
                    exibir(urgentes, 1); //Depois são exibidas as urgentes da última para a primeira tarefa
                } 
            }else {
                printf("\n"); 
            }
        } else if(acao == 'A'){
            int ID, paginas;
            char prioridade;
            scanf("%d", &ID); //Le o id
            scanf("%d", &paginas); //Le o número de páginas
            scanf(" %c", &prioridade); //LE a prioridade
            if(prioridade == 'N'){//Adiciona na fila certa de acordo com a prioridade
                adicionar(normais, ID, paginas, prioridade);
            } else {
                adicionar(urgentes, ID, paginas, prioridade); 
            }
        }
    }
    //Desaloca todas as memórias alocadas  
    liberar(normais);
    liberar(urgentes); 
   return 0; 
}