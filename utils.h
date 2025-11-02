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

#endif // UTILS_H
