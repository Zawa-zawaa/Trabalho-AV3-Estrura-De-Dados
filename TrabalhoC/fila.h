#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Cores para o terminal
#define COR_VERDE "\x1b[32m"
#define COR_AZUL "\x1b[34m"
#define COR_AMARELA "\x1b[33m"
#define COR_VERMELHA "\x1b[31m"
#define COR_RESET "\x1b[0m"

// Estrutura do trabalho de impressão
typedef struct {
    int id;
    char nomeArquivo[50];
    int pags;
    char tipo; // 'N' para Normal, 'P' para Prioritário
} Trabalho;

// Nó da fila
typedef struct NoFila {
    Trabalho info;
    struct NoFila* proximo;
} NoFila;

// Estrutura da fila
typedef struct {
    NoFila* inicio;
    NoFila* fim;
} Fila;

// Interface
void limparTela();
void exibirMenu();
void pausarTela();
int gerarID(Fila* fNormal, Fila* fPrioritaria);
int idExiste(Fila* fNormal, Fila* fPrioritaria, int id);
int contardados_c(Fila* fNormal, Fila* fPrioritaria);
int tipoValido(char tipo);
int senhaExiste(Fila* fNormal, Fila* fPrioritaria, int id);

// Operações da fila
void inicializarFila(Fila* f);
void inserirTrabalho(Fila* fNormal, Fila* fPrioritaria);
void inserirTrabalhoDireto(Fila* fNormal, Fila* fPrioritaria, int id, char nomeArquivo[], int pags, char tipo);
void processarTrabalho(Fila* fNormal, Fila* fPrioritaria);
void cancelarTrabalho(Fila* fNormal, Fila* fPrioritaria);
void listardados_c(Fila* fNormal, Fila* fPrioritaria);

// Persistência e memória
void salvarCSV(Fila* fNormal, Fila* fPrioritaria);
void carregarCSV(Fila* fNormal, Fila* fPrioritaria);
void liberarFila(Fila* f);

#endif