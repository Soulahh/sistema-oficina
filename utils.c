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

int ler_inteiro_positivo(const char* prompt){
    int valor, c;
    do{
        valor = ler_inteiro(prompt);
        if (valor <= 0){
            printf("Valor deve ser um inteiro positivo.\n");
        }
    } while (valor <= 0);
    return valor;
}

int tratar_data_fevereiro(int ano){
	if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) return 29; //bissexto
	return 28;
}

bool data_valida(int dia, int mes, int ano){
	int data_limite;
	switch(mes){
		case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: 
            data_limite = 31;
            break;
		case 4:
		case 6:
		case 9:
		case 11:
			data_limite = 30;
			break;
		case 2:
			data_limite = tratar_data_fevereiro(ano);
			break;
		default:
			return false;
			break;
	}
	return (dia < data_limite);
}

bool escolher_modo(const char* prompt){
	int modo;
	do{
		modo = ler_inteiro(prompt) - 1;
	} while(modo != 0 && modo != 1);
	return modo;
}
void exibir_menu(){
	puts("========= MENU =========");
    puts("1 - Exibir Clientes");
    puts("2 - Inserir Cliente");
    puts("3 - Buscar Cliente");
    puts("4 - Remover Cliente");
    puts("5 - Navegar na Lista de Clientes");
    puts("6 - Salvar Dados");
    puts("7 - Inserir Carro");
    puts("8 - Exibir Carros");
    puts("0 - Sair");
    printf("Selecione a Opção: ");
}

char* extrair_primeiro_nome(char* nomeCompleto){
	char* espaco = strchr(nomeCompleto, ' ');
	if (espaco != NULL){
		size_t tamanho = espaco - nomeCompleto;
		char* primeiroNome = (char *)malloc(tamanho+1);
		if(primeiroNome == NULL){perror("Alocação falhou!\n"); return NULL;}
		strncpy(primeiroNome, nomeCompleto, tamanho);
		primeiroNome[tamanho] = '\0';
		return primeiroNome;
	} else {
		char* primeiroNome = malloc(strlen(nomeCompleto)+1);
		if(primeiroNome == NULL){perror("Alocação falhou!\n"); return NULL;}
		strcpy(primeiroNome,nomeCompleto);
		return primeiroNome;
	}
}
