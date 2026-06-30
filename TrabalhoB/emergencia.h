#ifndef EMERGENCIA_H
#define EMERGENCIA_H

// 📚 1. Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

// 🎨 2. Constantes de Cores (Extras Gerais)
#define COR_VERMELHA "\x1b[31m"
#define COR_AMARELA "\x1b[33m"
#define COR_VERDE "\x1b[32m"
#define COR_RESET "\x1b[0m"

// 🏥 3. Definição das Structs (Tema B2)
typedef struct {
    int protocolo;            
    char nome[50];     
    char endereco[100]; 
    char telefone[15];  
    char tipoEmergencia[50]; 
    time_t dataHora;
}ChamadaEmergencia;

typedef struct NoPilha {
    ChamadaEmergencia dados;
    struct NoPilha* proximo; 
} NoPilha;

typedef struct {
    NoPilha* topo;
} Pilha;

// 4. Protótipos das Funções Utilitárias e Multiplataforma
void limparTela();
void pausarTela();
int contarChamadas(Pilha* pilha);
int protocoloExiste(Pilha* pilha, int protocoloBusca);

// 5. Protótipos das Funções Principais (Requisitos Obrigatórios)
void exibirMenu(Pilha* pilha);
void empilharChamada(Pilha* pilha);
void desempilharChamada(Pilha* pilha);

// 6. Protótipos de Persistência e Memória
void salvarCSV(Pilha* pilha);
void carregarCSV(Pilha* pilha);
void liberarPilhaCSV(Pilha* pilha);

#endif // EMERGENCIA_H  
