#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Códigos de cor ANSI (Para garantir pontos de extras gerais com interface amigável)
#define COR_VERMELHA "\x1b[31m"
#define COR_AMARELA "\x1b[33m"
#define COR_VERDE "\x1b[32m"
#define COR_RESET "\x1b[0m"

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