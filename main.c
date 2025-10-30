#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Esboço das structs
typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    char placa_carro[11];
    char modelo_carro[50];
    char cor_carro[50]; 
    Data data_entrada;
}DadosCarro;

typedef struct Carro{
    DadosCarro dados;
    struct Carro* proximo_carro;
} Carro;

typedef struct{
    Carro* primeiro;
    Carro* ultimo;
    size_t tamanho;
} ListaCarros;


typedef struct{
    int id;
    char nome[50];
    char num_telefone[20];
    char cpf[12];
    Data data_nasc;
    ListaCarros* carros;
} DadosCliente;


typedef struct Cliente{
    struct Cliente* anterior;
    struct Cliente* proximo;
    DadosCliente dados;
} Cliente;

typedef struct {
    Cliente* primeiro;
    Cliente* ultimo;
    size_t tamanho;
} ListaClientes;


int main(){
 
    
    return 0;
}