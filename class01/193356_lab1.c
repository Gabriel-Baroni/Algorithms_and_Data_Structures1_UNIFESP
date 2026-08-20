#include <stdio.h>
#define MAX 501

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

int verificarIgualdade(char string1[MAX], char string2[MAX]){
    int igual = 1; //boolean
    int i;
     while(i<MAX && string1[i] != '\0' && string2[i] != '\0'){ //Laço while para percorrer toda a string e verificar seu final "\0"
        if(string1[i] != string2[i]){ //Se algum caracter for diferente, muda a flag para 0 (falso)
            igual = 0;
            return igual; 
        } 
        i++; 
    }
    return igual; 
}

int main(){
    //Declaração das strings (vetores de char), uma variável auxiliar char (car) e um iterador (i)
    char string1[MAX]; 
    char string2[MAX]; 
    char car;
    int i = 0 ;

    //laço while para ler o input de caracter por caracter da primiera string. Esse laço perdura enquanto o iterador for menor que o máximo de caracteres e a varável auxiliar c for diferente de '\n' (Enter)
    while(i<MAX-1 && car != '\n'){
        scanf("%c", &car);
        string1[i] = car;
        i++;
    }

    string1[i] = '\0'; //Se saiu do laço, a string acabou, então acrescento um '\0' para fechar essa string
    i=0; //Zero o interador
    car='\0'; //Limpo a variável auxiliar

    //Mesmo laço while para ler a segunda string. 
    while(i<MAX-1 &&  car != '\n'){
        scanf("%c", &car);
        string2[i] = car;
        i++;
    }
    string2[i] = '\0';

    printf("%s", string1);
    printf("%s", string2);
    printf("%d %d %d", contaCaractere(string1), contaCaractere(string2), verificarIgualdade(string1, string2));  //Chamada das funções e print apropriado
    return 0;
}

