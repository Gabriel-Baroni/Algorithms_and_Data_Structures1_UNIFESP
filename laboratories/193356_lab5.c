// Neste exercício, você implementará uma simulação de um editor de texto simples que suporta as
// seguintes operações:
// 1. Inserir: Insere um caractere em uma posição específica do texto;
// 2. Remover: Remove um caractere de uma posição específica do texto;
// 3. Desfazer (undo): Desfaz a última operação realizada (inserção ou remoção);
// 4. Refazer (redo): Refaz a última operação desfeita.
// O editor deve gerenciar as edições do texto utilizando pilhas (stacks) para permitir que as operações de
// desfazer e refazer sejam executadas de maneira eficiente.


#include <stdio.h>
#include <stdlib.h>

//Estrutura de cada operação que pode ser empilhada. É basicamente um nó de uma lista simplesmente encadeada
typedef struct Operacao {
    char tipo; // ’I’ para inserir, ’R’ para remover
    char caractere; // caractere inserido ou removido
    int posicao; // posicao no texto onde a operacao ocorreu
    struct Operacao* prox; // ponteiro para a proxima operacao na pilha
} Operacao;

//Estrutura padrão de um lista
typedef struct pilha{
    Operacao* primeira;
}Pilha; 

//É a estrutura de um caractere do texto do editor. é um nó de uma lista duplamente encadeada
typedef struct caractere{
    char caractere;
    struct caractere* prox; 
    struct caractere* ant;
}Texto; 

//A estrutura do meu editor com um ponteiro para o texto e para as pilhas 
typedef struct editor{
    int tamanhoTexto;
    Texto* texto; 
    Pilha* desfazer; 
    Pilha* refazer; 
}Editor; 

//Função para criar e inicializar a pilha 
Pilha* criarPilha(){
    Pilha* nova = malloc(sizeof(Pilha));
    nova->primeira = NULL; 
    return nova; 
}
//Função para criar e inicializar o Editor
Editor* criarEditor(){
    Editor* novo = malloc(sizeof(Editor));
    novo->tamanhoTexto = 0;
    novo->texto = NULL;
    novo->refazer = criarPilha(); 
    novo->desfazer = criarPilha(); 
    return novo; 
}

//Função para criar uma operação e empilha-la em alguma pilha.
void criarOperacao(char tipo, char caractere, int posicao, Pilha* pilha){
    Operacao* nova = malloc(sizeof(Operacao));
    nova->caractere = caractere;
    nova->posicao = posicao;
    nova->tipo = tipo; 
    nova->prox = pilha->primeira; 
    pilha->primeira = nova;
}
//Função para esvaziar a pilha dando free em todos os seus elementos 
void esvaziarPilha(Pilha* pilha){
    if(pilha == NULL){
        return;
    }
    Operacao* atual = pilha->primeira;
    while(atual!= NULL){
        Operacao* prox = atual->prox;
        free(atual);
        atual= prox; 
    }
    pilha->primeira = NULL;
}

//Função para liberar o exto dando free em todos os nós da lista duplamente encadeada
void liberarTexto(Texto * texto){
    Texto* p = texto;
    while(p!=NULL){
        Texto * atual = p->prox;
        free(p);
        p = atual; 
    }
}
//Função para liberar o editor, usando as outras funções de free e dando free em seus campos
void liberarEditor(Editor* editor){
    if(editor == NULL){
        return;
    }
    liberarTexto(editor->texto);
    esvaziarPilha(editor->refazer);
    esvaziarPilha(editor->desfazer);
    free(editor->refazer);
    free(editor->desfazer);
    free(editor); 
}

//Função de inserir um elemento na lista duplamente encadeada. O parametro "registro" se da pois, quando uma função undo ou redo chama a função inserir, elas não devem inseri-las novamente em alguma pilha
Texto* inserir(Editor* editor, char caractere, int posicao, int registro){
    //Verificação de posição válida
    if(posicao>editor->tamanhoTexto || posicao < 0){
        return editor->texto; 
    }
    //Inicializa um contador
    int c = 0 ; 
    //Aloca o espaço para um novo nó (caractere)
    Texto* novo = malloc(sizeof(Texto));
    //Inicializa um ponteiro auxilair
    Texto* p = editor->texto; 
    //Inicializa os campos desse caractere (nó)
    novo->caractere = caractere;
    novo->prox = NULL;
    novo->ant = NULL;

    //Verifica se a lista está vazia e insere no inicio
     if(p == NULL){
        editor->texto = novo;
        editor->tamanhoTexto++;
        //Se registro for verdadeiro (1), vai ser criado uma operação e empilhada na pilha de desfazer e esvaziar a pilha de refazer
        if(registro) {
            criarOperacao('I', caractere, posicao, editor->desfazer); 
            esvaziarPilha(editor->refazer);
        }
        return editor->texto; 
    }

    //Se a lista não esta vazia, mas quer inserir no incio
    if(posicao == 0){
        novo->prox = p;
        p->ant=novo; 
        novo->ant = NULL;
        editor->texto = novo;
        editor->tamanhoTexto++;
        if(registro) {
            criarOperacao('I', caractere, posicao, editor->desfazer); 
            esvaziarPilha(editor->refazer);
        }
        return editor->texto; 
    }
    //Se quer inserir no final 
    if(posicao == editor->tamanhoTexto){
        while(p->prox!= NULL){
            p=p->prox;
            c++;
        }
        novo->prox = p->prox;
        novo->ant = p;
        p->prox = novo; 
        editor->tamanhoTexto++;
        if(registro) {
            criarOperacao('I', caractere, posicao, editor->desfazer); 
            esvaziarPilha(editor->refazer);
        }
        return editor->texto;
    }

    //Uma posição intermediaria
    while(c != posicao){
        p = p->prox;
        c++;
    }

    p->ant->prox = novo; 
    novo->prox = p;
    novo->ant = p->ant;
    p->ant = novo; 
    editor->tamanhoTexto++;
    if(registro) {
        criarOperacao('I', caractere, posicao, editor->desfazer); 
        esvaziarPilha(editor->refazer);
    }
    return editor->texto; 
}

//Função de remover um elemento na lista duplamente encadeada. O parametro "registro" se da pois, quando uma função undo ou redo chama a função remover, elas não devem inserir essa operacao em alguma pilha
Texto* remover(Editor* editor, int posicao, int registro){
    //Verificação de posição válida
     if(posicao > editor->tamanhoTexto-1 || posicao < 0){
        return editor->texto; 
    } 
    //Inicializando contador
    int c = 0 ; 
    //Inicializando ponteiro auxilair
    Texto* p = editor->texto; 

    //Verifica se a lista esta vazia
     if(p == NULL){
        return editor->texto; 
    }

    //Verifica se a lista só tem um elemento
    if(p->prox==NULL && p->ant ==NULL){
        editor->texto = NULL;
        //Se registro for verdadeiro (1), será criado uma operação e esta será empilhada na pilha de desfazer enquanto a pilha de refazer será envaziada
        if(registro) {
            criarOperacao('R', p->caractere, posicao, editor->desfazer); 
            esvaziarPilha(editor->refazer);
        }
        free(p); 
        editor->tamanhoTexto--;
        return editor->texto;
    }

    //Verifica se o elemento a ser removido e da primeira posição
    if(posicao == 0){
        editor->texto = p->prox;
        p->prox->ant = NULL; 
        if(registro) {
            criarOperacao('R', p->caractere, posicao, editor->desfazer); 
            esvaziarPilha(editor->refazer);
        }
        free(p); 
        editor->tamanhoTexto--;
        return editor->texto; 
    }

    //Percorre a lista até chegar no final ou achar a posição
    while(p->prox!= NULL && c!=posicao){
        p=p->prox;
        c++;
    }

    //Verifica se é o ultimo elemento
    if(p->prox==NULL){
        p->ant->prox = NULL; 
        if(registro) {
            criarOperacao('R', p->caractere, posicao, editor->desfazer); 
            esvaziarPilha(editor->refazer);
        } 
        free(p); 
        editor->tamanhoTexto--;
        return editor->texto;
    }

    //Caso em que o elemento está no meio
    p->ant->prox = p->prox;
    p->prox->ant = p->ant; 
    if(registro) {
        criarOperacao('R', p->caractere, posicao, editor->desfazer); 
        esvaziarPilha(editor->refazer);
    } 
    free(p); 
    editor->tamanhoTexto--;
    return editor->texto; 

}

//Função de desfazer
void undo(Editor* editor){
    if(editor->desfazer->primeira == NULL){
        return;
    }
    //Se a operação for de remover, o editor vai inserir esse caracter removido. O contrário é válido
    if(editor->desfazer->primeira->tipo=='R'){
        inserir(editor, editor->desfazer->primeira->caractere, editor->desfazer->primeira->posicao, 0);
    } else {
       remover(editor, editor->desfazer->primeira->posicao, 0);
    }
    //Ajusto o ponteiro das pilhas, o ponteiro do desfazer passa a apontar para o proximo dessa operação e o ponteiro do refazer apssa a apontar para essa operação
   Operacao* primeiro = editor->desfazer->primeira;
   editor->desfazer->primeira = editor->desfazer->primeira->prox;
   primeiro->prox = editor->refazer->primeira;
   editor->refazer->primeira = primeiro;
}

//Função de refazer 
void redo(Editor* editor){
     if(editor->refazer->primeira == NULL){
        return;
    }
    //Aqui a ordem é a mesma. Se a operação é de remover, o editor vai remover. O contrário também é válido
    if(editor->refazer->primeira->tipo =='R'){
        remover(editor, editor->refazer->primeira->posicao, 0);
    } else {
       inserir(editor, editor->refazer->primeira->caractere, editor->refazer->primeira->posicao, 0);
    }
   Operacao* primeiro = editor->refazer->primeira;
   editor->refazer->primeira = editor->refazer->primeira->prox;
   primeiro->prox = editor->desfazer->primeira;
   editor->desfazer->primeira = primeiro;
}

int main(){
    //Inicialização das variáveis
    int n, m, pos; 
    char* vet; 
    char escolha, caractere;
    Editor* editor;

    //Leitura da varoiavel n que gaurada o tamanho do texto incial
    scanf("%d", &n);

    //Vetor alocado dinamicamente para guardar esse texto incial
    vet = malloc(n*sizeof(char));

    //Leitura de cada caractere do texto inicial
    for(int i=0; i<n; i++){
        scanf(" %c", &vet[i]);
    }

    //Cria e incializa o editor
    editor = criarEditor();

    //Vai inserir os caracteres do texto incial como nós da lista duplamente encadeada. Repare que essas ações de inserção não serão empilhadas
    for(int i=0; i<n; i++){
        editor->texto = inserir(editor, vet[i],i, 0);
    }


    //Leirtua da varaiavel m. Número de operações
    scanf("%d", &m);

    //Laço para pergar as operações e realizar as chamadas das funções
    for(int i =0 ; i<m; i++){
        scanf(" %c", &escolha);
        if(escolha == 'U'){
            undo(editor);
        } else if(escolha == 'E'){
            redo(editor); 
        } else if(escolha=='R'){
            scanf(" %d", &pos);
            editor->texto = remover(editor, pos, 1);
        }else if(escolha=='I'){
            scanf(" %c", &caractere);
            scanf(" %d", &pos);
            editor->texto = inserir(editor, caractere, pos, 1);
        }
        //Sempre que acaba uma operação, mostra o texto. Para isso, precisa varrer a lista 
        Texto* p = editor->texto;
        while(p!=NULL){
            printf("%c", p->caractere);
            p=p->prox;
        }
        printf("\n");
    }
    //Liberar as estruturas
    free(vet);
    liberarEditor(editor); 
    return 0;
}
