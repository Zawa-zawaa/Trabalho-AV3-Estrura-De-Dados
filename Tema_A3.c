#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Códigos de cor ANSI (Para garantir pontos de extras gerais com interface amigável)
#define COR_VERMELHA "\x1b[31m"
#define COR_AMARELA "\x1b[33m"
#define COR_VERDE "\x1b[32m"
#define COR_RESET "\x1b[0m"

// Função para limpar a tela
void limparTela() {
    #ifdef _WIN32
        // Se o sistema for Windows (32 ou 64 bits)
        system("cls");
    #else
        // Se o sistema for Linux ou macOS (Unix-like)
        system("clear");
    #endif
}

// Função para pausar a tela e aguardar o usuário
void pausarTela() {
    printf("\n[Pressione ENTER para continuar...]");
    
    // Limpa o buffer caso tenha sobrado algum '\n' do scanf anterior
    // (Substituto mais seguro e multiplataforma para o fflush(stdin) ou system("pause"))
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
    getchar(); // Aguarda o usuário apertar ENTER
}

// O ponteiro 'inicio' é o "cabeça" da nossa lista encadeada.
// Como não há pacientes cadastrados ainda, ele aponta para NULL (vazio).
No* inicio = NULL;

// 1. A estrutura de dados exigida pelo tema
typedef struct {
    int senha;        // Deve ser única
    char nome[50];
    int idade;
    int gravidade;    // 1 a 4 (1 é maior prioridade)
} Paciente;

// 2. A estrutura do NÓ (Alocação Dinâmica)
typedef struct No {
    Paciente dados;       // Guarda as informações do paciente
    struct No* proximo;   // Ponteiro que aponta para o próximo paciente da fila
} No;

void criarno(int senha, char nome[], int idade, int gravidade);
void inserirOrdenado(int senha, char nome[], int idade, int gravidade);

void exibirMenu(No* inicio) {
    limparTela();
    int total = contarPacientes(inicio);
    
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(COR_VERMELHA "       HOSPITAL - TRIAGEM (A3)\n" COR_RESET);
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(" Pacientes na fila atual: %d\n\n", total);
    
    printf(" 1 - Cadastrar novo paciente (Inserir)\n");
    printf(" 2 - Buscar paciente por senha\n");
    printf(" 3 - Editar dados do paciente\n");
    printf(" 4 - Atender paciente (Excluir)\n");
    printf(" 5 - Listar todos os pacientes\n");
    printf(" 0 - Salvar e Sair\n");
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(" Escolha uma opcao: ");
}