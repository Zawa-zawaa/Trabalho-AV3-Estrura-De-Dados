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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


// 🏥 3. Definição das Structs (Tema B2)
typedef struct {
    int protocolo;            
    char nome[50];    
    char endereco[100]; 
    char tipoEmergencia[50]; 
    char dataHora[10];
    char telefone[20];  
}ChamadaEmergencia;


// -- Prototipos --

// Menus -

void limparTela();
void pausarTela();
void exibirMenu();

//

// Utilitarios --
int contarRegistros(FILE *arquivo);
void lercsv(ChamadaEmergencia *Chamadas);
void listarChamadas(ChamadaEmergencia *Chamadas,int quant);
void consultarUltimaChamada(ChamadaEmergencia *Chamadas,int quant);
void registrarChamada(ChamadaEmergencia **Chamadas,int *quant);

#endif // EMERGENCIA_H  
