#include "emergencia.h"


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

int contarRegistros(FILE* arquivo) {
    char linha[100];
    int quant = -1;
    while (fgets(linha, 100, arquivo)) {
        quant++;
    }

    rewind(arquivo);
    return quant;
}



void lercsv(ChamadaEmergencia* Chamadas) {
    FILE* arquivo = fopen("dados_b.csv", "r");
    char linha[100];
    fgets(linha, 100, arquivo);  // pula primeira linha
    int i = 0;
    while (fgets(linha, 100, arquivo)) {
        Chamadas[i].protocolo = atoi(strtok(linha, ","));

        strcpy(Chamadas[i].nome, strtok(NULL, ","));
        strcpy(Chamadas[i].endereco, strtok(NULL, ","));
        strcpy(Chamadas[i].tipoEmergencia, strtok(NULL, ","));
        strcpy(Chamadas[i].dataHora, strtok(NULL, ","));
        strcpy(Chamadas[i].telefone, strtok(NULL, ","));
        Chamadas[i].telefone[strcspn(Chamadas[i].telefone, "\r\n")] = '\0';
        i++;
    }

    fclose(arquivo);
}

void listarChamadas(ChamadaEmergencia* Chamadas, int quant) {
    limparTela();
    printf(COR_VERMELHA "--- LISTA DE CHAMADAS ---\n\n" COR_RESET);
    for (int i = 0; i < quant; i++) {
        printf("Protocolo: %d\n", Chamadas[i].protocolo);
        printf("Nome: %s\n", Chamadas[i].nome);
        printf("Endereco: %s\n", Chamadas[i].endereco);
        printf("Telefone: %s\n", Chamadas[i].telefone);
        printf("Tipo: %s\n", Chamadas[i].tipoEmergencia);
        printf("Data/Hora: %s\n", Chamadas[i].dataHora);
        printf("\n\n");
    }
}

void consultarUltimaChamada(ChamadaEmergencia* Chamadas, int quant) {
    limparTela();
    printf(COR_VERMELHA "--- ULTIMA CHAMADA REGISTRADA ---\n\n" COR_RESET);

    printf("Protocolo: %d\n", Chamadas[quant-1].protocolo);
    printf("Nome: %s\n", Chamadas[quant-1].nome);
    printf("Endereco: %s\n", Chamadas[quant-1].endereco);
    printf("Telefone: %s\n", Chamadas[quant-1].telefone);
    printf("Tipo: %s\n", Chamadas[quant-1].tipoEmergencia);
    printf("Data/Hora: %s\n", Chamadas[quant-1].dataHora);
    printf("\n\n");
}

void registrarChamada(ChamadaEmergencia **Chamadas,int *quant){
    limparTela();
    printf(COR_VERMELHA "--- CADASTRAR EMERGENCIA ---\n\n" COR_RESET);
    ChamadaEmergencia c;
    getchar(); // limpa o '\n' deixado pelo scanf


    // adicionar validacao depois

    if (*quant == 0){
        c.protocolo = 1001;

    }else{
        c.protocolo = (*Chamadas)[(*quant) - 1].protocolo + 1;

    }

    printf("\nDigite o Nome do Cliente: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Digite o Endereco: ");
    fgets(c.endereco, sizeof(c.endereco), stdin);
    c.endereco[strcspn(c.endereco, "\n")] = '\0';

    printf("Digite o Tipo da Emergencia: ");
    fgets(c.tipoEmergencia, sizeof(c.tipoEmergencia), stdin);
    c.tipoEmergencia[strcspn(c.tipoEmergencia, "\n")] = '\0';

    printf("Digite o Horario: ");
    fgets(c.dataHora, sizeof(c.dataHora), stdin);
    c.dataHora[strcspn(c.dataHora, "\n")] = '\0';

    printf("Digite o Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    (*quant)++;

    ChamadaEmergencia *temp = realloc(*Chamadas,(*quant) * sizeof(ChamadaEmergencia));

    if(temp == NULL){
        printf("alocacao falhou");
        return;
    }
    *Chamadas = temp;
    

    (*Chamadas)[(*quant)-1] = c;

    FILE *arquivo = fopen("dados_b.csv", "w");

    for(int i = 0;i<(*quant);i++){

        fprintf(arquivo,
            "%d,%s,%s,%s,%s,%s\n",
            (*Chamadas)[i].protocolo,
            (*Chamadas)[i].nome,
            (*Chamadas)[i].endereco,
            (*Chamadas)[i].tipoEmergencia,
            (*Chamadas)[i].dataHora,
            (*Chamadas)[i].telefone

        );

    }

    fclose(arquivo);





}
