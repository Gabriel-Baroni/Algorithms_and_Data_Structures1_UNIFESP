#include <stdio.h>
#include <stdlib.h>

//-=-=--=-=--=-=--=-=-ESTRUTURAS E FUNÇÕES PARA A PILHA-=-=--=-=--=-=--=-=-

//Declaração do nó da arvore para ser usado na pilha e fila
typedef struct arv{
    int info;
    struct arv* esq;
    struct arv* dir;
}Arv;

typedef struct no{
    Arv* info;
    struct no* prox;
}NoPilha;

typedef struct pilha{
    NoPilha* prim;
}Pilha;

Pilha* criar_pilha(){
    Pilha* p = malloc(sizeof(Pilha));
    p->prim = NULL;
    return p; 
} 

void push(Pilha* p, Arv* v){
    NoPilha* novo = malloc(sizeof(NoPilha));
    novo->info = v;
    novo->prox = p->prim;
    p->prim = novo;  
}

Arv* pop(Pilha* p){
    if(p->prim == NULL){
        return NULL;
    }
    NoPilha* removido = p->prim;
    Arv* v = removido->info; 
    p->prim = removido->prox;
    free(removido); 
    return v;
}

Arv* verTopo(Pilha* p){
    if(p->prim == NULL){
        return NULL;
    }
    Arv* v = p->prim->info; 
    return v;

}

void liberar_pilha(Pilha* p){
    NoPilha* no = p->prim;
    while(no!=NULL){
        NoPilha* aux = no->prox;
        free(no);
        no = aux; 
    }
    free(p);
} 

//-=-=--=-=--=-=--=-=-ESTRUTURAS E FUNÇÕES PARA A FILA-=-=--=-=--=-=--=-=-
typedef struct nofila{
    Arv* info;
    struct nofila* prox;
}NoFila;

typedef struct fila{
    NoFila* inicio;
    NoFila* fim;
}Fila; 

Fila* criar_fila(){
    Fila* f = malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void insere_fila(Fila* f, Arv* v){
    NoFila* novo = malloc(sizeof(NoFila));
    novo->info = v;
    novo->prox = NULL;
    if(f->inicio == NULL){
        f->inicio = novo;
    }else{
        f->fim->prox = novo;
    }
    f->fim = novo; 
}

Arv* retirar_fila(Fila* f){
    if(f->inicio == NULL){
        return NULL;
    }
    Arv* valor = f->inicio->info;
    NoFila* noExcluido = f->inicio;
    f->inicio = f->inicio->prox;
    if(f->inicio ==NULL){
        f->fim = NULL;
    }
    free(noExcluido); 
    return valor;
}

void liberarFila(Fila* f){
    if(f==NULL){
        return;
    }
    NoFila* no = f->inicio;
    while(no != NULL){
        NoFila* aux = no->prox;
        free(no);
        no = aux;  
    }
    free(f); 
}


//-=-=--=-=--=-=--=-=-ESTRUTURAS E FUNÇÕES PARA A ABB-=-=--=-=--=-=--=-=-


//Cria uma árvore vazia 
Arv* criar_vazia(){
    return NULL;
}

//Verifica se a árvore está vazia
int vazia (Arv* raiz){
    return raiz == NULL;
}

//Insere um elemento na árvore, seguindo as regras de uma ABB
Arv* insere(Arv* raiz, int v){
    if(vazia(raiz)){
        raiz = malloc(sizeof(Arv));
        raiz->info = v;
        raiz->esq = NULL;
        raiz->dir = NULL; 
    }else if(raiz->info > v){
        raiz->esq = insere(raiz->esq, v); 
    }else if(raiz->info < v){
        raiz->dir = insere(raiz->dir, v);
    }
    return raiz; 
}

//Percorre a árvore em pré-ordem de forma recursiva
void preOrdem(Arv* raiz){
    if(vazia(raiz)){
        return;
    }
    printf("%d", raiz->info);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir); 
}

//Percorre a árvore em ordem de forma recursiva
void emOrdem(Arv* raiz){
    if(vazia(raiz)){
        return;
    }
    emOrdem(raiz->esq);
    printf("%d", raiz->info);
    emOrdem(raiz->dir); 
}

//Percorre a árvore em pós-ordem de forma iterativa
void posOrdem(Arv* raiz){
    //Verifica se a árvore esta vazia
    if(vazia(raiz)){
        return;
    }
    //Captura a raiz
    Arv* atual = raiz;
    //Variável auxiliar para guardar elementos já visitados
    Arv* anterior = NULL;
    //Pilha criada para simular o funcionamento da recursividade na stack da memória RAM
    Pilha* pilha = criar_pilha();
    //Repete o loop enquanto a pilha estiver com algum elemento OU o nó atual for diferente de NULL
    while(pilha->prim != NULL|| atual!=NULL){ //Precisa desse atual!= NULL pois se não eu irira adicionar dois nós raiz na pilha
        //Percorre todos os nós da SAE e vai adicionando eles na pilha
        while(atual!=NULL){
            push(pilha, atual);
            atual=atual->esq;
        }
        //Se saiu do laço, quer dizer que chegou em um nó que não tem mais filhos a esquerda
        Arv* topo = verTopo(pilha); //Essa função serve para capturar o topo da pilha (ultimo push), sem dar pop nele
        //Se esse elemento tiver filho a direita e ainda não foi visitado
        if(topo->dir !=NULL && topo->dir != anterior){
            atual = topo->dir;
        }else{
            //Se ele não tem filho na direita (folha) ou já foi visitado
            printf("%d", topo->info);
            anterior = pop(pilha);
        }
    }
    liberar_pilha(pilha); 
}

void porNivel (Arv* raiz){
    //Verifica se a árvore está vazia
    if(raiz==NULL){
        return;
    }
    //Cria uma fila 
    Fila* fila = criar_fila();
    //Insere a raiz da árvore na fila 
    insere_fila(fila, raiz);
    //Enquanto a fila estiver vazia 
    while(fila->inicio!= NULL){
        //Pega o primeiro da fila
        Arv* atual = retirar_fila(fila);
        //Coloca o filho da esquerda, se tiver
        if(atual->esq !=NULL){
            insere_fila(fila, atual->esq);
        }
        //Coloca o filho da direita, se tiver
        if(atual->dir !=  NULL){
            insere_fila(fila, atual->dir);
        }
        //Imprime o nó em questão
        printf("%d", atual->info);
    }
    liberarFila(fila); 
}

//Realiza busca binária na árvore
int buscar(Arv* raiz, int v){
    if(vazia(raiz)){
        return 0;
    }
    if(raiz->info == v){
        return 1;
    }else if(raiz->info > v){
        return buscar(raiz->esq, v); 
    } else{
        return buscar(raiz->dir, v); 
    }
}

//Função para liberar todos os nós da árvore (precisa ser em pós-ordem)
void liberar_arv(Arv* raiz){
    if(raiz == NULL) return;
    liberar_arv(raiz->esq);
    liberar_arv(raiz->dir);
    free(raiz); 
}

int main(){
    //Declaração e inicialização de variáveis e estruturas
    int n, *lista, v;
    //Números de elementos a serem inseridos
    scanf("%d", &n);
    //Alocamento dinâmico de um vetor de int de tamanho n
    lista = malloc(n*sizeof(int));
    //Inicialização de uma árvore
    Arv* arvore = criar_vazia();

    //Preechendo o vetor com os valores
    for(int i=0; i<n; i++){
        scanf("%d", &lista[i]); 
    } 

    //Valor a ser buscado
    scanf("%d", &v);

    //Insere cada elemento na árvore
    for(int i=0; i<n; i++){
        arvore = insere(arvore, lista[i]);
    } 

    //Imprime em pré-ordem
    preOrdem(arvore);
    printf("\n");
    //Imprime em ordem
    emOrdem(arvore); 
    printf("\n");
    //Imprime em pós-ordem
    posOrdem(arvore);
    printf("\n");
    //Imprime em nível
    porNivel(arvore); 
    printf("\n");
    //Imprime em se existe ou não o elemento buscado
    printf("%d", buscar(arvore, v));
    printf("\n");

    //Liberar estruturas 
    liberar_arv(arvore); 
    free(lista); 
    return 0; 
}