// * Descricao: Programa para contagem de letras, digitos e caracteres especiais e comparacao lexicografica de duas strings.
#include <stdio.h>
#define MAX 501

/*
 * Funcao: contaCaractere
 * Conta letras (l), digitos (d) e caracteres especiais (c).
 * Retorna o resultado da expressao: (l - d) * c
 */
int contaCaractere(char string[MAX]){
    int i = 0; 
    int l=0, d=0, c=0; //Declaração dos contadores
    //Laço while para percorrer a string enquanto o iterador for menor que o máximo ou chegar ao final da string '\0'
    while(i<MAX && string[i] != '\0' && string[i] != '\n'){
        if(string[i] >='A' && string[i]<='Z' || string[i] >='a' && string[i]<='z'){ //Utilizando os valores da tabela ASCII para determinar qual caracter é uma letra (maiúscula ou minúscula)
            l++; 
        } else if (string[i] >= '0' && string[i] <= '9'){ //Se não é uma letra, verifica se está entre um valor de digito da tabela ASCII
            d++; 
        } else{ //Se não for letra nem digito, é considerado caractere especial
            c++; 
        }
        i++; 
    }
    return (l-d)*c; //Retorna o valor socilitado
}

/*
 * Funcao: verificarIgualdade
 * Compara duas strings caractere por caractere.
 * Retorna 1 se forem iguais e 0 se forem diferentes.
 */
int verificarIgualdade(char string1[MAX], char string2[MAX]){
    int i = 0; //inicializa a variavel
     while(string1[i] != '\0' && string2[i] != '\0'){ //Laço while para percorrer toda a string e verificar seu final "\0"
        if(string1[i] != string2[i]){ //Se algum caracter for diferente, retorna 0
            return 0; 
        } 
        i++; 
    }

    if (string1[i] == string2[i]) { //se as strings tem o mesmo tamanho e nenhum caracter diferente retorna 1
        return 1; 
    } 
    return 0; 
}

int main(){
    //Declaração das strings (vetores de char), uma variável auxiliar char (car) e um iterador (i)
    char string1[MAX]; 
    char string2[MAX]; 
    char car = ' ';
    int i = 0 ;

    //laço while para ler o input de caracter por caracter da primiera string. Esse laço perdura enquanto o iterador for menor que o máximo de caracteres e a varável auxiliar car for diferente de '\n' (Enter)
    while(i<MAX-1 && scanf("%c", &car) == 1 && car != '\n'){ //Lê o char dentro da condição do while para verificar se deu certo
        if(car != '\r'){
            string1[i] = car;
            i++;
        }
    }

    string1[i] = '\0'; //Se saiu do laço, a string acabou, então acrescento um '\0' para fechar essa string
    i=0; //Zero o interador
    car='\0'; //Limpo a variável auxiliar

    //Mesmo laço while para ler a segunda string. 
    while(i<MAX-1 && scanf("%c", &car) == 1 && car != '\n'){
        if(car != '\r'){
            string2[i] = car;
            i++;
        }
        
    }
    string2[i] = '\0';
    
    printf("%d %d %d\n", contaCaractere(string1), contaCaractere(string2), verificarIgualdade(string1, string2));  //Chamada das funções e print apropriado
    return 0;
}