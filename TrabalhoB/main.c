#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -- Define --
#define COR_VERMELHA "\x1b[31m"
#define COR_AMARELA "\x1b[33m"
#define COR_VERDE "\x1b[32m"
#define COR_RESET "\x1b[0m"

//



// -- Structs --

typedef struct Chamada{
    int protocolo;
    char nome[255];
    char local[255];
    char tipo[100];
    char horario[50];
    char telefonr[15]
} Chamada;




//

// -- variaveis globais --

Chamada vetorChamadas[50];






// -- Prototipos --
void limparTela() {
    #ifdef _WIN32
        // Se o sistema for Windows (32 ou 64 bits)
        system("cls");
    #else
        // Se o sistema for Linux ou macOS (Unix-like)
        system("clear");
    #endif
}
void pausarTela() {
    printf("\n[Pressione ENTER para continuar...]");
    
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
    getchar();
}
void exibirMenu() {
    limparTela();
    
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(COR_VERMELHA "       Chamadas de Emergência (B3)\n" COR_RESET);
    printf(COR_AMARELA "========================================\n" COR_RESET);
    
    printf(" 1 - Registrar chamada\n");
    printf(" 2 - Consultar ultima chamada\n");
    printf(" 3 - Atender Chamada\n");
    printf(" 4 - Listar todas as chamadas\n");
    printf(" 0 - Salvar e Sair\n");
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(" Escolha uma opcao: ");
}

//

/*
typedef struct Chamada{
    int protocolo;
    char local[255];
    char tipo[100];
    char horario[50];
} Chamada;
*/


int main(){

    // -- Arquivo csv -- 

    FILE *arquivo = fopen("dados_b.csv", "r");
    char linha[100];
    
    while(fgets(linha,100,arquivo)){
        char *protocolo_str = strtok(linha, ",");
        char *local = strtok(NULL, ",");
        char *tipo_ocorrencia = strtok(NULL, ",");
        char *horario = strtok(NULL, ",");

        int protocolo = atoi(protocolo_str);

    }
    fclose(arquivo);

    int inputUser;
    do{
        
        




        scanf("%d",&inputUser);
    }while(inputUser);


    return 0;
}














