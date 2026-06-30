#ifndef TRIAGEM_H
#define TRIAGEM_H

// 📚 1. Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// 🎨 2. Constantes de Cores (Extras Gerais)
#define COR_VERMELHA "\x1b[31m"
#define COR_AMARELA "\x1b[33m"
#define COR_VERDE "\x1b[32m"
#define COR_RESET "\x1b[0m"

// 🏥 3. Definição das Structs (Tema A3)
typedef struct {
    int senha;        
    char nome[50];    
    int idade;        
    int gravidade;    
} Paciente;

// Estrutura do Nó para a Lista Encadeada (Extra Dinâmico)
typedef struct No {
    Paciente dados;
    struct No* proximo;
} No;

// 4. Protótipos das Funções Utilitárias e Multiplataforma
void limparTela();
void pausarTela();
int contarPacientes(No* inicio);
int senhaExiste(No* inicio, int senhaBusca);

// 5. Protótipos das Funções Principais (Requisitos Obrigatórios)
void exibirMenu(No* inicio);
void inserirOrdenado(No** inicio);
void buscarPaciente(No* inicio);
void editarPaciente(No* inicio);
void atenderPaciente(No** inicio); // Função de Remoção
void listarPacientes(No* inicio);

// 6. Protótipos de Persistência e Memória
void salvarCSV(No* inicio);
void carregarCSV(No** inicio);
void liberarLista(No** inicio);

#endif // Fim da proteção do cabeçalho