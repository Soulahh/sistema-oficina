#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#include <locale.h>

typedef struct{
    int dia, mes, ano;
} Data;

typedef struct{
    int id;
    char nome[50];
    char cpf[15];
    char email[50];
    char telefone[15];
    Data data_nasc;
} Clientes;

typedef struct Node_Clientes {
    Clientes dados_clientes;
    struct Node_Clientes *prev;
    struct Node_Clientes *next;
} Node_Clientes;

typedef struct{
    int id;
    char modelo[50];
    int ano;
    Data data_entrada;
    char cpf_cliente[15];
	char cor[50];
} Carros;

typedef struct Node_Carros {
    Carros dados_carros;
    struct Node_Carros *prev;
    struct Node_Carros *next;
} Node_Carros;

typedef struct{
    Node_Carros *begin;
    Node_Carros *end;
    size_t size;
} Lista_Carros;

typedef struct{
    Node_Clientes *begin;
    Node_Clientes *end;
    size_t size;
} Lista;

//Função de limpeza
bool lista_vazia(Lista* l) {
	return (l->size == 0);
}
//Verificação de Lista Vazia Carros
bool lista_vazia_carros(Lista_Carros* l) {
	return (l->size == 0);
}


//alocação da Lista de Clientes
Lista* alocar_lista() {
	Lista* l = (Lista *) calloc(1, sizeof(Lista));
	if(l == NULL) {
		printf("\nAlocação Falhou!\n\n");
		exit(1);
	}
	l->begin = NULL;
	l->end = NULL;
	l->size = 0;
	return l;
}
//alocação da Lista de Carros
Lista_Carros* alocar_lista_carros() {
	Lista_Carros* l = (Lista_Carros *) calloc(1, sizeof(Lista_Carros));
	if(l == NULL) {
		printf("\nAlocação Falhou!\n\n");
		exit(1);
	}
	l->begin = NULL;
	l->end = NULL;
	l->size = 0;
	return l;
}

//Verificação de Lista Vazia Clientes


void desalocar_lista(Lista **l_ref) {
	Lista* l = *l_ref;
	Node_Clientes* node = l->begin;
	Node_Clientes* aux = NULL;
	while(node != NULL) {
		aux = node;
		node = node->next;
		free(aux);
	}
	free(l);
	*l_ref = NULL;
}

void desalocar_lista_carros(Lista_Carros **l_ref) {
	Lista_Carros* l = *l_ref;
	Node_Carros* node = l->begin;
	Node_Carros* aux = NULL;
	while(node != NULL) {
		aux = node;
		node = node->next;
		free(aux);
	}
	free(l);
	*l_ref = NULL;
}

//==========================================CLIENTES========================================

//gerar id do cliente
int gerar_id(){
    static int id_atual = 0;
    return id_atual++;
}

//ler dados do cliente
Clientes* inserir_dados_cliente(){
    Clientes* cliente = (Clientes *) calloc(1, sizeof(Clientes));
    cliente->id = gerar_id();
    printf("\n");
    puts("===== CADASTRO DE CLIENTES =====");
    printf("Digite o Nome: ");
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = '\0';
    
    printf("Digite o Email: ");
    fgets(cliente->email, sizeof(cliente->email), stdin);
    cliente->email[strcspn(cliente->email, "\n")] = '\0';
    
    printf("Digite o CPF: ");
    fgets(cliente->cpf, sizeof(cliente->cpf), stdin);
    cliente->cpf[strcspn(cliente->cpf, "\n")] = '\0';
    
    printf("Digite o Telefone: ");
    fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = '\0';
    
	do{
		puts("Data de Nascimento:");
		cliente->data_nasc.dia = ler_inteiro_positivo("Dia: ");
		cliente->data_nasc.mes = ler_inteiro_positivo("Mês: ");
		cliente->data_nasc.ano = ler_inteiro_positivo("Ano: ");
	}while(!(data_valida(cliente->data_nasc.dia, cliente->data_nasc.mes, cliente->data_nasc.ano)));
    
    printf("Usuário %s Cadastrado com Sucesso!\n\n", cliente->nome);
    return cliente;
}

//alocação do nó de Clientes
Node_Clientes* alocar_node(Clientes* cliente) {
    //aloca um nó
    //pois cada cliente é inserido 1 por 1
	Node_Clientes* node = (Node_Clientes *) calloc(1, sizeof(Node_Clientes));
	if(node == NULL) {
		printf("\nAlocação Falhou\n\n");
		exit(1);
	}
	//no nó, os dados do cliente passados por parâmetro
	//são colocados dentro do nó
	//e são colocados também dentro da Struct Clientes
	//como são strings, precisam ser copiadas para o destino
	node->dados_clientes.id = cliente->id;
	strcpy(node->dados_clientes.nome, cliente->nome);
	strcpy(node->dados_clientes.email, cliente->email);
	strcpy(node->dados_clientes.cpf, cliente->cpf);
	strcpy(node->dados_clientes.telefone, cliente->telefone);
	node->dados_clientes.data_nasc.dia = cliente->data_nasc.dia;
	node->dados_clientes.data_nasc.mes = cliente->data_nasc.mes;
	node->dados_clientes.data_nasc.ano = cliente->data_nasc.ano;

	node->prev = NULL;
	node->next = NULL;
	return node;
}

//inserir cliente(nó) na lista
//vai ser sempre adicionado ao final da lista
void inserir_cliente(Lista* l, Node_Clientes* node) {
	if(lista_vazia(l)) {
		l->begin = node;
		l->end = node;
	} else {
		Node_Clientes* node_antigo = l->end;
		node->prev = node_antigo;
		node->next = NULL;
		node_antigo->next = node;
		l->end = node;
	}
	//a cada inserção, o tamanho da lista aumenta
	l->size++;
}

//verificar se cliente existe
bool cliente_existente(Lista* l, char* cpf){
    Node_Clientes* node_atual = l->begin;
    while(node_atual != NULL){
        if(strcmp(node_atual->dados_clientes.cpf, cpf) == 0){
            return true;
        }
        node_atual = node_atual->next;
    }
    return false;
}

//buscar contato na lista de Clientes pelo CPF
void buscar_contato_cpf(Lista* l, char* cpf){
    Node_Clientes* node_atual = l->begin;
    int encontrado = 0;
    if(lista_vazia(l)){
        printf("\nLista Vazia!\n\n");
        return;
    }
    while(node_atual != NULL){
    if(strcmp(node_atual->dados_clientes.cpf, cpf) == 0){
        encontrado = 1;
        printf("\nCliente %s Encontrado!\n", node_atual->dados_clientes.nome);
        printf("ID: %d\n", node_atual->dados_clientes.id);
	    printf("Email: %s\n\n", node_atual->dados_clientes.email);
	    break;
    }
    node_atual = node_atual->next;
    }
    if(encontrado == 0){
        printf("\nNão Encontrado!\n\n");
    }
}

void buscar_contato_nome(Lista* lista, char* nome){
	Node_Clientes* node_atual = lista->begin;
	int qtd_matches = 0;
	if(lista_vazia(lista)){printf("Lista vazia!\n");return;}
	while(node_atual != NULL){
		if(strcasecmp(node_atual->dados_clientes.nome,nome) == 0){
			char* nome_cliente = extrair_primeiro_nome(node_atual->dados_clientes.nome);
			if(qtd_matches == 0) printf("\nCliente Encontrado!\n");
			qtd_matches++;
			printf("Nome:     %s\n", node_atual->dados_clientes.nome);
			printf("ID:       %d\n", node_atual->dados_clientes.id);
			printf("CPF:      %s\n",node_atual->dados_clientes.cpf);
			printf("Email:    %s\n", node_atual->dados_clientes.email);
			printf("Telefone: %s\n\n", node_atual->dados_clientes.telefone);
			free(nome_cliente);
		}
		node_atual = node_atual->next;
	}
	if(qtd_matches == 0){
		printf("\nCliente não encontrado!\n");
	}
}

//remover CARRO da lista pelo CPF
//só vai ser chamada quando um cliente for removido.
void remover_carro_cpf(Lista_Carros* l, char* cpf){
    if(lista_vazia_carros(l)){
        printf("\nLista Vazia!\n\n");
        return;
    }
    Node_Carros* node_atual = l->begin;
    Node_Carros* node_proximo = NULL;
    int contagemCarro = 0;
    while(node_atual != NULL){
        
        node_proximo = node_atual->next;
        
        if(strcmp(node_atual->dados_carros.cpf_cliente, cpf) == 0){
            if(node_atual->prev == NULL && node_atual->next == NULL){
                l->begin = NULL;
                l->end = NULL;
            }
            else if(node_atual->prev == NULL){
                l->begin = node_atual->next;
                node_atual->next->prev = NULL;
            }
            else if(node_atual->next == NULL){
                l->end = node_atual->prev;
                l->end->next = NULL;
            }
            else{
                //o proximo do anterior, aponta pro proximo atual
                node_atual->prev->next = node_atual->next;
                // o anterior do proximo aponta pro anterior do atual
                node_atual->next->prev = node_atual->prev;
            }
            free(node_atual);
            l->size--;
            contagemCarro++;
            break;
        }
        node_atual = node_proximo;
    if(contagemCarro > 0){
        printf("\n%d Carro(s) do Cliente também foram removidos!\n");
    }
    }
}

//remover CLIENTE da lista pelo CPF
void remover_contato_cpf(Lista* l, Lista_Carros* lista_carros, char* cpf){
    if(lista_vazia(l)){
        printf("\nLista Vazia!\n\n");
        return;
    }
	clear_screen();
    Node_Clientes* node_atual = l->begin;
    int encontrado = 0;
    while(node_atual != NULL){
        if(strcmp(node_atual->dados_clientes.cpf, cpf) == 0){
            encontrado = 1;
            remover_carro_cpf(lista_carros, cpf);
            
            if(node_atual->prev == NULL && node_atual->next == NULL){
                l->begin = NULL;
                l->end = NULL;
            }
            else if(node_atual->prev == NULL){
                l->begin = node_atual->next;
                node_atual->next->prev = NULL;
            }
            else if(node_atual->next == NULL){
                l->end = node_atual->prev;
                l->end->next = NULL;
            }
            else{
                //o proximo do anterior, aponta pro proximo atual
                node_atual->prev->next = node_atual->next;
                // o anterior do proximo aponta pro anterior do atual
                node_atual->next->prev = node_atual->prev;
            }
            printf("\nCliente Removido com Sucesso!\n\n");
            free(node_atual);
            l->size--;
            break;
        }
        node_atual = node_atual->next;
    }
    if(encontrado == 0){
        printf("\nCliente não Encontrado!\n\n");
    }
}


void gerenciar_remocao_nome(Lista* lista, Lista_Carros* lista_carros, char* nome){
	Node_Clientes* node_atual = lista->begin;
	char cpf[15];
	int qtd_matches = 0;
	if(lista_vazia(lista)){printf("Lista vazia!\n");return;}
	while(node_atual != NULL){
		if(strcasecmp(node_atual->dados_clientes.nome,nome) == 0){
			if(qtd_matches == 0) printf("\nCliente Encontrado!\n");
			qtd_matches++;
			printf("Nome:     %s\n", node_atual->dados_clientes.nome);
			printf("ID:       %d\n", node_atual->dados_clientes.id);
			printf("CPF:      %s\n\n",node_atual->dados_clientes.cpf);
		}
		node_atual = node_atual->next;
	}
	if(qtd_matches == 0){
		printf("\nCliente não encontrado!\n"); return;
	} else {
		printf("\nDigite o CPF do cliente que deseja remover: ");
		fgets(cpf, sizeof(cpf), stdin);
		cpf[strcspn(cpf, "\n")] = '\0';
		remover_contato_cpf(lista, lista_carros, cpf);
	}
} 
//navegar na Lista de clientes
void navegar_lista(Lista* l) {
	if(lista_vazia(l)){
	    printf("\nLista Vazia!\n\n");
	    return;
	}
	Node_Clientes* node_atual = l->begin;
	int opc = -1;
	while(opc != 0){
	    
	puts("---- Navegação de Contatos ----");
	printf("Atual: [ID %d] %s\n", 
           node_atual->dados_clientes.id, 
           node_atual->dados_clientes.nome);
	if(node_atual->prev == NULL){
	    printf("Anterior: (Início da Lista)\n");
	}else{
	    printf("Anterior: %s\n", node_atual->prev->dados_clientes.nome);
	}
	if(node_atual->next == NULL){
	    printf("Próximo: (Fim da Lista)\n\n");
	}else{
	    printf("Próximo: %s\n", node_atual->next->dados_clientes.nome);
	}
	printf("\n");
	puts("Opções de Navegação:");
	puts("1 - Ir para o Próximo");
	puts("2 - Ir para o Anterior");
	puts("0 - Para Voltar ao Menu");
	printf("Selecione a Opção de Navegação: ");
	scanf("%d", &opc);
	getchar();
	switch(opc){
	    case 1:
	    //se o proximo for diferente de nulo, ele vai pro proximo
			clear_screen();
			if(node_atual->next != NULL) {
				node_atual = node_atual->next;
			}else{
				printf("\nEste é o último contato!\n\n");
			}
			break;
	    case 2:
	    //se o anterior for diferente de nulo, ele vai pro anterior
			clear_screen();
			if(node_atual->prev != NULL) {
				node_atual = node_atual->prev;
			}else{
				printf("\nNão há contato anterior!\n\n");
			}
			break;
	    case 0:
			clear_screen();
			break;
	    default:
			clear_screen();
			puts("\nOpção Inválida!\n\n");
			break;
	}
	}
}

//exibir a lista de clientes
void imprimir_lista(Lista* l) {
    //pega o valor do inicio da lista
	Node_Clientes* node_atual = l->begin;
	if(lista_vazia(l)){
	    printf("\nA Lista está vazia!\n\n");
	    return;
	}
	//percorre a lista até ser NULL
	//imprime e depois atualiza o valor para o próximo 
	printf("\n");
	puts(" ===== Lista de Clientes =====");
	while(node_atual != NULL){
	   printf("ID:         %d\n", node_atual->dados_clientes.id);
	   printf("Nome:       %s\n", node_atual->dados_clientes.nome);
	   printf("Email:      %s\n", node_atual->dados_clientes.email);
	   printf("CPF:        %s\n", node_atual->dados_clientes.cpf);
	   printf("Telefone:   %s\n",node_atual->dados_clientes.telefone);
	   printf("Data de Nascimento: %02d/%02d/%04d\n\n",node_atual->dados_clientes.data_nasc.dia,node_atual->dados_clientes.data_nasc.mes,node_atual->dados_clientes.data_nasc.ano);
	   node_atual = node_atual->next;
	}
}

//==========================================CARROS========================================

//gerar id do carro
int gerar_id_carro(){
    static int id_atual = 0;
    return id_atual++;
}

//ler dados do Carro
Carros* inserir_dados_carro(Lista* lista_clientes){
    if(lista_vazia(lista_clientes)){
        printf("\nÉ necessário ter clientes cadastrados para inserir um carro.\n");
        return NULL;
    }
    Carros* carro = (Carros *) calloc(1, sizeof(Carros));
    carro->id = gerar_id_carro();
    printf("\n");
    puts("===== CADASTRO DE CARROS =====");
    printf("Digite o Modelo: ");
    fgets(carro->modelo, sizeof(carro->modelo), stdin);
    carro->modelo[strcspn(carro->modelo, "\n")] = '\0';

	printf("Digite a Cor: ");
	fgets(carro->cor, sizeof(carro->cor), stdin);
	carro->cor[strcspn(carro->cor, "\n")] = '\0';
    
    printf("Digite o CPF do Cliente Dono: ");
    fgets(carro->cpf_cliente, sizeof(carro->cpf_cliente), stdin);
    carro->cpf_cliente[strcspn(carro->cpf_cliente, "\n")] = '\0';
    
    if(cliente_existente(lista_clientes, carro->cpf_cliente) == false){
        printf("\nCPF Inválido! Não encontrado no banco de clientes.\n");
        free(carro);
        return NULL;
    }
    
    printf("Ano do Carro: ");
    scanf("%d", &carro->ano);
    getchar();
    
	do{
		puts("Data de Entrada:");
		carro->data_entrada.dia = ler_inteiro_positivo("Dia:");
		carro->data_entrada.mes = ler_inteiro_positivo("Mês: ");
		carro->data_entrada.ano = ler_inteiro_positivo("Ano: ");
	}while(!(data_valida(carro->data_entrada.dia, carro->data_entrada.mes,carro->data_entrada.ano)));

    printf("Carro %s Cadastrado com Sucesso!\n\n", carro->modelo);
    return carro;
}

//alocação do nó de Carros
Node_Carros* alocar_node_carros(Carros* carro) {
    //aloca um nó
    //pois cada cliente é inserido 1 por 1
	Node_Carros* node = (Node_Carros *) calloc(1, sizeof(Node_Carros));
	if(node == NULL) {
		printf("\nAlocação Falhou\n\n");
		exit(1);
	}
	//no nó, os dados do carro passados por parâmetro
	//são colocados dentro do nó
	//e são colocados também dentro da Struct Carro
	//como são strings, precisam ser copiadas para o destino
	node->dados_carros.id = carro->id;
	strcpy(node->dados_carros.modelo, carro->modelo);
	strcpy(node->dados_carros.cpf_cliente, carro->cpf_cliente);
	node->dados_carros.data_entrada.dia = carro->data_entrada.dia;
	node->dados_carros.data_entrada.mes = carro->data_entrada.mes;
	node->dados_carros.data_entrada.ano = carro->data_entrada.ano;
	node->dados_carros.ano = carro->ano;
	strcpy(node->dados_carros.cor, carro->cor);
	node->prev = NULL;
	node->next = NULL;
	return node;
}

//inserir carro(nó) na lista
//vai ser sempre adicionado ao final da lista
void inserir_carro(Lista_Carros* l, Node_Carros* node) {
	if(lista_vazia_carros(l)){
		l->begin = node;
		l->end = node;
	} else {
		Node_Carros* node_antigo = l->end;
		node->prev = node_antigo;
		node->next = NULL;
		node_antigo->next = node;
		l->end = node;
	}
	//a cada inserção, o tamanho da lista aumenta
	l->size++;
}

//bucando o cliente pelo cpf
//pra imprimir ele na lista de carros
Node_Clientes* buscar_contato_carro_cpf(Lista* l, char* cpf){
    Node_Clientes* node_atual = l->begin;
    
    while(node_atual != NULL){
        if(strcmp(node_atual->dados_clientes.cpf, cpf) == 0){
            return node_atual;
        }
        node_atual = node_atual->next;
    }
    return NULL;
}

//exibir a lista de carros
void imprimir_lista_carros(Lista* lista_clientes, Lista_Carros* l) {
    //pega o valor do inicio da lista
	Node_Carros* node_atual = l->begin;
	if(lista_vazia_carros(l)){
	    printf("\nA Lista está vazia!\n\n");
	    return;
	}
	//percorre a lista até ser NULL
	//imprime e depois atualiza o valor para o próximo 
	printf("\n");
	puts(" ===== Lista de Carros =====");
	while(node_atual != NULL){
	    printf("ID: %d\n", node_atual->dados_carros.id);
	    printf("Modelo: %s\n", node_atual->dados_carros.modelo);
		printf("Cor: %s\n", node_atual->dados_carros.cor);
	    
	    //atribui o cpf ligado ao carro para a variável
	    char* cpf_cliente = node_atual->dados_carros.cpf_cliente;
	    //envia a variável pra função de buscar o cpf do cliente
	    Node_Clientes* cliente_dono = buscar_contato_carro_cpf(lista_clientes, cpf_cliente);
	    
	    if(cliente_dono != NULL){
	        printf("Cliente: %s\n", cliente_dono->dados_clientes.nome);
	        printf("CPF: %s\n", cliente_dono->dados_clientes.cpf);
	    }else{
	        printf("\nCPF do Cliente não encontrado!\n\n");
	    }
	    printf("\n");
	    node_atual = node_atual->next;
	}
}

void salvar_clientes(const char* arquivo_csv, Lista* lista){
		FILE* f = fopen(arquivo_csv, "w");
		if(f == NULL){perror("Erro na abertura do arquivo CSV!");return;}
		fprintf(f, "id_cliente,nome,cpf,email,telefone,data_nasc\n");
		Node_Clientes* cliente_atual  = lista->begin;
		while(cliente_atual != NULL){
			fprintf(f, "%d,%s,%s,%s,%s,%02d/%02d/%04d\n",
				cliente_atual->dados_clientes.id,
				cliente_atual->dados_clientes.nome,
				cliente_atual->dados_clientes.cpf,
				cliente_atual->dados_clientes.email,
				cliente_atual->dados_clientes.telefone,
				cliente_atual->dados_clientes.data_nasc.dia,
				cliente_atual->dados_clientes.data_nasc.mes,
				cliente_atual->dados_clientes.data_nasc.ano);
			cliente_atual = cliente_atual->next;
		}
		fclose(f);
}

void salvar_carros(const char* arquivo_csv, Lista_Carros* lista_carros){
	FILE* f = fopen(arquivo_csv, "w");
	if(f==NULL){perror("Erro na abertura do arquivo CSV!");return;}
	fprintf(f,"id_carro,cpf_cliente,modelo,cor,ano,data_entrada\n");
	Node_Carros* carro_atual = lista_carros->begin;
	while(carro_atual != NULL){
		fprintf(f, "%d,%s,%s,%s,%d,%02d/%02d/%04d\n",
			carro_atual->dados_carros.id,
			carro_atual->dados_carros.cpf_cliente,
			carro_atual->dados_carros.modelo,
			carro_atual->dados_carros.cor,
			carro_atual->dados_carros.ano,
			carro_atual->dados_carros.data_entrada.dia,
			carro_atual->dados_carros.data_entrada.mes,
			carro_atual->dados_carros.data_entrada.ano
		);
		carro_atual = carro_atual->next;
	}
	fclose(f);
}

void recuperar_clientes(const char* arquivo_csv, Lista* lista){
	FILE* f = fopen(arquivo_csv, "r");
	char linha[1024];
	int contador = 0;
	if(f == NULL) return;
	fgets(linha,sizeof(linha), f); //ignorando o header
	while(fgets(linha,sizeof(linha),f)){
		linha[strcspn(linha,"\n")] = '\0';
		if(linha[0] == '\0') continue;
		Clientes* cliente_atual = (Clientes *) calloc(1, sizeof(Clientes));
        if (!cliente_atual) {
            fprintf(stderr, "Erro ao alocar memória para cliente\n");
            fclose(f);
            return;
        }
		char* token = strtok(linha,",");
		int campo = 0;
		while (token != NULL){
			switch(campo){
				case 0:
					cliente_atual->id = atoi(token);
					break;
				case 1:
					strcpy(cliente_atual->nome,token);
					break;
				case 2:
					strcpy(cliente_atual->cpf,token);
					break;
				case 3:
					strcpy(cliente_atual->email, token);
					break;
				case 4:
					strcpy(cliente_atual->telefone,token);
					break;
				case 5:
					int dia, mes, ano;
					sscanf(token,"%d/%d/%d",&dia,&mes,&ano);
					cliente_atual->data_nasc.dia = dia;
					cliente_atual->data_nasc.mes = mes;
                    cliente_atual->data_nasc.ano = ano;
					break;
				default:
					break;
			}
			campo++;
			token = strtok(NULL,",");
		}
		Node_Clientes* node_atual = alocar_node(cliente_atual);
		inserir_cliente(lista,node_atual);
		free(cliente_atual);
		contador++;
		}
	fclose(f);
	for(int i = 0; i < contador; i++) gerar_id();
	printf("Clientes recuperados com sucesso!\n");
}

void recuperar_carros(const char* arquivo_csv, Lista_Carros* lista_carros){
	FILE* f = fopen(arquivo_csv,"r");
	if(f==NULL)return;
	char linha[1024];
	
	fgets(linha,sizeof(linha),f);
	while(fgets(linha,sizeof(linha),f)){
		linha[strcspn(linha,"\n")] = '\0';

		if(linha[0] == '\0') continue;
		Carros* carro_atual = (Carros*) calloc(1,sizeof(Carros));
		if (!carro_atual) {
            fprintf(stderr, "Erro ao alocar memória para carro\n");
            fclose(f);
            return;
        }
		char* token = strtok(linha,",");
		int campo = 0;
		while(token != NULL){
			switch(campo){
				case 0:
					carro_atual->id = atoi(token);
					break;
				case 1:
					strcpy(carro_atual->cpf_cliente, token);
					break;
				case 2:
					strcpy(carro_atual->modelo,token);
					break;
				case 3:
					strcpy(carro_atual->cor,token);
					break;
				
				case 4:
					carro_atual->ano = atoi(token);
					break;
				case 5:
					int dia, mes, ano;
					sscanf(token,"%d/%d/%d",&dia,&mes,&ano);
					carro_atual->data_entrada.dia = dia;
					carro_atual->data_entrada.mes = mes;
					carro_atual->data_entrada.ano = ano;
					break;
				default:
					break;
			}
			campo++;
			token = strtok(NULL,",");
		}
		Node_Carros* node_atual = alocar_node_carros(carro_atual);
		inserir_carro(lista_carros,node_atual);
		free(carro_atual);
		lista_carros->size++;
	}
	fclose(f);
}

void recuperar_dados(Lista_Carros* lista_carros, Lista* lista){
	recuperar_clientes("clientes.csv",lista);
	recuperar_carros("carros.csv", lista_carros);
}

int main()
{
	setlocale(LC_ALL,"");
	system("chcp 65001");
	clear_screen();
    int opc = -1;
    Lista* lista = alocar_lista();
    Lista_Carros* lista_carros = alocar_lista_carros();
	recuperar_dados(lista_carros,lista);
    do{
    exibir_menu();
    scanf("%d", &opc);
    getchar();
	char cpf[15];
	char nome[100];
	int modo;
    switch(opc){
			case 1:
			clear_screen();
			imprimir_lista(lista);
			break;
        case 2:
			clear_screen();
			Clientes* cliente = inserir_dados_cliente();
			Node_Clientes* node = alocar_node(cliente);
			inserir_cliente(lista, node);
			free(cliente);
			break;
        case 3:
			clear_screen();
			modo = escolher_modo("Escolha método de busca:\n1 - Nome\n2 - CPF\nSelecione o método: ");
			clear_screen();
			if(modo){
				printf("Busque o CPF: ");
				fgets(cpf, sizeof(cpf), stdin);
				cpf[strcspn(cpf, "\n")] = '\0';
				buscar_contato_cpf(lista, cpf);
			} else {
				printf("Busque o Nome: ");
				fgets(nome, sizeof(nome),stdin);
				nome[strcspn(nome,"\n")] = '\0';
				buscar_contato_nome(lista, nome);
			}
			break;
        case 4:
			clear_screen();
			modo = escolher_modo("Escolha método de deleção:\n1 - Nome\n2 - CPF\nSelecione o método:");
			if(modo){
				printf("Insira o CPF para Remover: ");
				fgets(cpf, sizeof(cpf), stdin);
				cpf[strcspn(cpf, "\n")] = '\0';
				remover_contato_cpf(lista, lista_carros, cpf);	
			} else {
				printf("Busque o Nome: ");
				fgets(nome, sizeof(nome), stdin);
				nome[strcspn(nome,"\n")] = '\0';
				gerenciar_remocao_nome(lista, lista_carros, nome);
			}
			break;
        case 5:
			clear_screen();
			navegar_lista(lista);
			break;
        case 6:
			clear_screen();
			salvar_clientes("clientes.csv",lista);
			salvar_carros("carros.csv",lista_carros);
        	break;
        case 7:
			clear_screen();
			Carros* carro = inserir_dados_carro(lista);
			if(carro != NULL){
				Node_Carros* node_carro = alocar_node_carros(carro);
				inserir_carro(lista_carros, node_carro);
				free(carro);
			}
			break;
        case 8:
			clear_screen();
			imprimir_lista_carros(lista, lista_carros);
			break;
        case 0:
			clear_screen();
			printf("\nEncerrando...\n");
			break;
        default:
			clear_screen();
			printf("\nOpção inválida!\n\n");
			break;
    }
    } while(opc != 0);
    
    desalocar_lista(&lista);
    desalocar_lista_carros(&lista_carros);
    return 0;
}
