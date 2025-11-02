#ifndef UTILS_H
#define UTILS_H

    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdbool.h>

    // Mapeamento de funções para compatibilidade Windows
    #ifdef _WIN32
        #define strcasecmp _stricmp
        #define strncasecmp _strnicmp
    #endif

    // Funções utilitárias
    void clear_screen(void);
    int ler_inteiro(const char* prompt);
    int ler_inteiro_positivo(const char* prompt);
    int tratar_data_fevereiro(int ano);
    bool data_valida(int dia, int mes, int ano);
    bool escolher_modo(const char* prompt);
    void exibir_menu(void);
    char* extrair_primeiro_nome(char* nomeCompleto);
#endif
