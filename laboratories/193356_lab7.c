#include <stdio.h>
#include <stdlib.h>

int verifica_palindromo(char *str, int inicio, int fim) {
    if (inicio >= fim) {
        return 1; 
    }
    
    if (str[inicio] != str[fim]) {
        return 0; 
    }
    
    return verifica_palindromo(str, inicio + 1, fim - 1);
}

int main(void) {
    int num_strings, tamanho_max;
    int i, len;
    char c;
    char *palavra = NULL;
    char *resultados = NULL;

    if (scanf("%d %d", &num_strings, &tamanho_max) != 2) {
        return 1;
    }

    do {
        c = fgetc(stdin);
    } while (c != '\n' && c != EOF);

    palavra = (char *)malloc((tamanho_max + 2) * sizeof(char));
    resultados = (char *)malloc((num_strings + 1) * sizeof(char));

    if (palavra == NULL || resultados == NULL) {
        if (palavra != NULL) free(palavra);
        if (resultados != NULL) free(resultados);
        return 1;
    }

    for (i = 0; i < num_strings; i++) {
        if (fgets(palavra, tamanho_max + 2, stdin) != NULL) {
            len = 0;
            while (palavra[len] != '\0' && palavra[len] != '\n' && palavra[len] != '\r') {
                len++;
            }
            
            if (verifica_palindromo(palavra, 0, len - 1)) {
                resultados[i] = '1';
            } else {
                resultados[i] = '0';
            }
        } else {
            resultados[i] = '0';
        }
    }
    
    resultados[num_strings] = '\0';

    fputs(resultados, stdout);
    fputs("\n", stdout);

    free(palavra);
    free(resultados);

    return 0;
}