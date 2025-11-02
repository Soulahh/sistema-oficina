#include "utils.h"
#include <stdlib.h>

void clear_screen(void) {
#if defined(_WIN32) || defined(WIN32)
    system("cls");
#else
    system("clear");
#endif
}
int ler_inteiro(const char* prompt){
    int valor, c, sucesso;
    do{
        printf("%s",prompt);
        sucesso = scanf("%d", &valor);
        if(sucesso != 1){
            printf("Entrada inválida. Tente novamente!\n");
        }
        while ((c = getchar()) != '\n' && c != EOF);
    } while(sucesso != 1);
    return valor;
}