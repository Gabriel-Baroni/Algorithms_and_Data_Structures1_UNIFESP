#include <stdio.h>
#include <stdlib.h>

//O argc é um inteiro que representa a quantidade de argumentos a serem enviados (considerando o nome do arquivo do próprio programa c)
//O argv é  um vetor de ponteiros do tipo char que armazena a string de cada parâmetro passado
int main(int argc, char *argv[]){
    //Verfiica se a quantidade de parâmetros é a esperada
    if(argc != 5){
        printf("Quantidade errada de parâmetros"); 
        exit(1);
    }
    //Abre os arquivos com a função fopen(char* nome_arquivo, char* modo)
    //--> nome_arquivo: é um ponteiro para o primeiro elemento de um vetor de caracteres (string) que aramazena o caminho do arquivo
    //--> modo: é um ponteiro para o primieiro elemento de um vetor de caracteres (string) que aramazena em que modo você vai abrir o arquivo
    //Retorno: Retorna um ponteiro do tipo FILE, se abriu corretamente, ou NULL caso tenha dado algum erro
    FILE* entrada_bin = fopen(argv[1], "rb"); 
    FILE* saida_txt = fopen(argv[2], "w+");
    FILE* entrada_txt = fopen(argv[3], "a+");
    FILE* saida_bin = fopen(argv[4], "wb"); 

    //Verifica se os arquivos foram abertos corretamente, se um não foi, fecha todos e acaba o programa
    if(!entrada_bin || !saida_bin || !entrada_txt || !saida_txt){
        if(entrada_bin){
            fclose(entrada_bin);
        }
        if(saida_bin){
            fclose(saida_bin);
        }
        if(entrada_txt){
            fclose(entrada_txt);
        }
        if(saida_txt){
            fclose(saida_txt); 
        }
        exit(1); 
    }
    //Um vetor para guardar temporariamente os numeros lidos do arquivo entrada_bin
    int num[3]; 
    //Lê arquivos binários com a função: fread(void *ptr, size_t size, size_t count, FILE* stream)
    //--> ptr:É o ponteiro para o espaço na memória onde os dados lidos ficarão armazenados
    //-->size: É o tamanho (em bytes) de cada elemento a ser lido
    //--> count: É a quantidade de elementos a serem lidos
    //-->stream: É um ponteiro do tipo FILE para o arquivo de onde os dados serão lidos
    //Retorno: O número de elementos lidos. Se for menor do que o passado pelo count, significa EOF (End of file) 
    //Lê o conteúdo de entrada_bin e escreve em saida_txt
    while(fread(num, sizeof(int), 3, entrada_bin) == 3){
        //Escreve em arquivos de texto com a função: fprinf(File* stream, char* format, ...)
        //stream -> É o ponteiro do tipo File para o arquivo onde os dados serão gravados
        //format-> é uma string para os identificadores de formato
        //... -> São os dados a serem gravados
        fprintf(saida_txt, "%d %d %d\n",  num[0], num[1], num[2]); 
    }
    fclose(entrada_bin); //Fecha o arquivo
    fflush(saida_txt); //Descarrega todo o conteúdo do buffer e grava no disco
    rewind(saida_txt); //Volta o ponteiro para o início do arquivo saida_txt
        //Lê arquivos de texto com a função: fscanf(File* stream, char* format, ...)
        //stream -> É o ponteiro do tipo File para o arquivo onde os dados serão lidos
        //format-> é uma string para os identificadores de formato
        //... -> São os endereços de memória para armezenar as informações lidas
    //Lê o conteúdo de saida_txt e escreve em entrada_txt
    while(fscanf(saida_txt, "%d %d %d\n", &num[0], &num[1], &num[2]) == 3){
        fprintf(entrada_txt, "%d %d %d\n", num[0], num[1], num[2]); 
    }
    //Descarrega o conteúdo do buffer e fecha o arquivo
    fflush(saida_txt);
    fclose(saida_txt); 

    //Descarrega o conteúdo do buffer e coloca o ponteiro no início
    fflush(entrada_txt);
    rewind(entrada_txt);
    //Lê o conteúdo de entrada_txt e escreve no saida_bin
    while(fscanf(entrada_txt, "%d %d %d\n", &num[0], &num[1], &num[2]) == 3){
        fwrite(num, sizeof(int), 3, saida_bin);  
    }

    //Descarrega o conteúdo do buffer e fecha o arquivo
    fflush(entrada_txt);
    fclose(entrada_txt);

    //Descarrega o conteúdo do buffer e fecha o arquivo
    fflush(saida_bin);
    fclose(saida_bin);
    return 0;

}