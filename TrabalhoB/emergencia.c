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
    printf(" 5 - Buscar Emergencia\n");
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

    printf(COR_VERMELHA "\n================ LISTA DE CHAMADAS ================\n" COR_RESET);

    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("| %-8s | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
           "Prot", "Nome", "Endereco", "Tipo", "Data/Hora", "Telefone");
    printf("-----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < quant; i++) {
        printf("| %-8d | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
               Chamadas[i].protocolo,
               Chamadas[i].nome,
               Chamadas[i].endereco,
               Chamadas[i].tipoEmergencia,
               Chamadas[i].dataHora,
               Chamadas[i].telefone);
    }

    printf("-----------------------------------------------------------------------------------------------------\n");
}

void consultarUltimaChamada(ChamadaEmergencia* Chamadas, int quant) {
    limparTela();

    printf(COR_VERMELHA "\n========= ULTIMA CHAMADA REGISTRADA =========\n" COR_RESET);

    if (quant > 0) {
        printf("-----------------------------------------------------------------------------------------------------\n");

        printf("| %-8s | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
               "Prot", "Nome", "Endereco", "Tipo", "Data/Hora", "Telefone");
        printf("-----------------------------------------------------------------------------------------------------\n");


        printf("| %-8d | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
               Chamadas[quant - 1].protocolo,
               Chamadas[quant - 1].nome,
               Chamadas[quant - 1].endereco,
               Chamadas[quant - 1].tipoEmergencia,
               Chamadas[quant - 1].dataHora,
               Chamadas[quant - 1].telefone);

        printf("-----------------------------------------------------------------------------------------------------\n");

    } else {
        printf("\nNenhuma chamada cadastrada.\n");
    }
}

void registrarChamada(ChamadaEmergencia** Chamadas, int* quant) {
    limparTela();
    printf(COR_VERMELHA "--- CADASTRAR EMERGENCIA ---\n\n" COR_RESET);
    ChamadaEmergencia c;
    getchar();  // limpa o '\n' deixado pelo scanf


    // adicionar validacao depois

    if (*quant == 0) {
        c.protocolo = 1001;

    } else {
        c.protocolo = (*Chamadas)[(*quant) - 1].protocolo + 1;
    }

    printf("\nDigite o Nome do Cliente: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';
    if (strlen(c.nome) == 0) {
        printf("Nome invalido!\n");
        return;
    }

    printf("Digite o Endereco: ");
    fgets(c.endereco, sizeof(c.endereco), stdin);
    c.endereco[strcspn(c.endereco, "\n")] = '\0';
    if (strlen(c.endereco) == 0) {
        printf("Endereco invalido!\n");
        return;
    }

    printf("Digite o Tipo da Emergencia: ");
    fgets(c.tipoEmergencia, sizeof(c.tipoEmergencia), stdin);
    c.tipoEmergencia[strcspn(c.tipoEmergencia, "\n")] = '\0';
    if (strlen(c.tipoEmergencia) == 0) {
        printf("Tipo de emergencia invalido!\n");
        return;
    }

    printf("Digite o Horario (HH:MM): ");
    fgets(c.dataHora, sizeof(c.dataHora), stdin);
    c.dataHora[strcspn(c.dataHora, "\n")] = '\0';

    if (strlen(c.dataHora) != 5 ||
        c.dataHora[2] != ':' ||
        c.dataHora[0] < '0' || c.dataHora[0] > '9' ||
        c.dataHora[1] < '0' || c.dataHora[1] > '9' ||
        c.dataHora[3] < '0' || c.dataHora[3] > '9' ||
        c.dataHora[4] < '0' || c.dataHora[4] > '9') {
        printf("Horario invalido! Use HH:MM\n");
        return;
    }

    printf("Digite o Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    int len = strlen(c.telefone);

    if (len < 8 || len > 15) {
        printf("Telefone invalido!\n");
        return;
    }

    // verifica se só tem números
    for (int i = 0; i < len; i++) {
        if (c.telefone[i] < '0' || c.telefone[i] > '9') {
            printf("Telefone deve conter apenas numeros!\n");
            return;
        }
    }

    (*quant)++;

    ChamadaEmergencia* temp = realloc(*Chamadas, (*quant) * sizeof(ChamadaEmergencia));

    if (temp == NULL) {
        printf("alocacao falhou");
        return;
    }
    *Chamadas = temp;


    (*Chamadas)[(*quant) - 1] = c;

    FILE* arquivo = fopen("dados_b.csv", "w");
    fprintf(arquivo, "protocolo,nome,endereco,tipoEmergencia,dataHora,telefone\n");
    for (int i = 0; i < (*quant); i++) {
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


void atenderChamada(ChamadaEmergencia** Chamadas, int* quant) {
    if ((*quant) > 0) {
        limparTela();

        printf(COR_AMARELA "================ CHAMADA ATENDIDA ================\n" COR_RESET);

        printf("-----------------------------------------------------------------------------------------------------\n");

        printf("| %-8s | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
               "Prot", "Nome", "Endereco", "Tipo", "Data/Hora", "Telefone");
        printf("-----------------------------------------------------------------------------------------------------\n");


        printf("| %-8d | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
               (*Chamadas)[(*quant) - 1].protocolo,
               (*Chamadas)[(*quant) - 1].nome,
               (*Chamadas)[(*quant) - 1].endereco,
               (*Chamadas)[(*quant) - 1].tipoEmergencia,
               (*Chamadas)[(*quant) - 1].dataHora,
               (*Chamadas)[(*quant) - 1].telefone);

        printf("-----------------------------------------------------------------------------------------------------\n");


        printf(COR_VERDE "\nStatus: FINALIZADO\n" COR_RESET);

        
        (*quant)--;

        if (*quant == 0) {
            free(*Chamadas);
            *Chamadas = NULL;
        } else {
            ChamadaEmergencia* temp =
                realloc(*Chamadas, (*quant) * sizeof(ChamadaEmergencia));

            if (temp == NULL) {
                printf("Erro de alocacao!\n");
                return;
            }

            *Chamadas = temp;
        }

        
        FILE* arquivo = fopen("dados_b.csv", "w");

        if (arquivo == NULL) {
            printf("Erro ao abrir arquivo!\n");
            return;
        }

        fprintf(arquivo, "protocolo,nome,endereco,tipoEmergencia,dataHora,telefone\n");

        for (int i = 0; i < (*quant); i++) {
            fprintf(arquivo,
                    "%d,%s,%s,%s,%s,%s\n",
                    (*Chamadas)[i].protocolo,
                    (*Chamadas)[i].nome,
                    (*Chamadas)[i].endereco,
                    (*Chamadas)[i].tipoEmergencia,
                    (*Chamadas)[i].dataHora,
                    (*Chamadas)[i].telefone);
        }

        fclose(arquivo);

    } else {
        printf("\nNenhuma chamada na fila.\n");
    }
}

void buscarChamada(ChamadaEmergencia* Chamadas, int quant) {
    limparTela();

    printf(COR_VERMELHA "\n========== BUSCAR EMERGENCIA ==========\n" COR_RESET);

    if (quant <= 0) {
        printf("\nNenhuma chamada cadastrada.\n");
        return;
    }

    printf("Digite o protocolo: ");
    int inputuser;
    scanf("%d", &inputuser);

    int encontrado = 0;

    for (int i = 0; i < quant; i++) {
        if (Chamadas[i].protocolo == inputuser) {
            printf("\n---------------- RESULTADO ----------------\n");
            printf("-----------------------------------------------------------------------------------------------------\n");

            printf("| %-8s | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
                   "Prot", "Nome", "Endereco", "Tipo", "Data/Hora", "Telefone");
            printf("-----------------------------------------------------------------------------------------------------\n");

            printf("| %-8d | %-15s | %-20s | %-15s | %-12s | %-12s |\n",
                   Chamadas[i].protocolo,
                   Chamadas[i].nome,
                   Chamadas[i].endereco,
                   Chamadas[i].tipoEmergencia,
                   Chamadas[i].dataHora,
                   Chamadas[i].telefone);

            printf("-----------------------------------------------------------------------------------------------------\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nProtocolo nao encontrado.\n");
    }
}