#include "fila.h"

int gerarID(Fila* fNormal, Fila* fPrioritaria) {
    int id;
    do {
        printf("Digite o ID do trabalho: ");
        scanf("%d", &id);
        if (idExiste(fNormal, fPrioritaria, id)) {
            printf(COR_AMARELA "ID ja existe. Digite outro.\n" COR_RESET);
        }
    } while (idExiste(fNormal, fPrioritaria, id));
    return id;
}

int idExiste(Fila* fNormal, Fila* fPrioritaria, int id) {
    NoFila* atual = fNormal->inicio;
    while (atual != NULL) {
        if (atual->info.id == id) return 1;
        atual = atual->proximo;
    }

    atual = fPrioritaria->inicio;
    while (atual != NULL) {
        if (atual->info.id == id) return 1;
        atual = atual->proximo;
    }

    return 0;
}

int contardados_c(Fila* fNormal, Fila* fPrioritaria) {
    int cont = 0;
    NoFila* atual = fNormal->inicio;

    while (atual != NULL) {
        cont++;
        atual = atual->proximo;
    }

    atual = fPrioritaria->inicio;
    while (atual != NULL) {
        cont++;
        atual = atual->proximo;
    }

    return cont;
}

int tipoValido(char tipo) {
    return (tipo == 'N' || tipo == 'n' || tipo == 'P' || tipo == 'p');
}

int senhaExiste(Fila* fNormal, Fila* fPrioritaria, int id) {
    return idExiste(fNormal, fPrioritaria, id);
}

void inicializarFila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void inserirTrabalhoDireto(Fila* fNormal, Fila* fPrioritaria, int id, char nomeArquivo[], int pags, char tipo) {
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf(COR_VERMELHA "Erro de alocacao de memoria.\n" COR_RESET);
        return;
    }

    novo->info.id = id;
    strncpy(novo->info.nomeArquivo, nomeArquivo, sizeof(novo->info.nomeArquivo) - 1);
    novo->info.nomeArquivo[sizeof(novo->info.nomeArquivo) - 1] = '\0';
    novo->info.pags = pags;
    novo->info.tipo = tipo;
    novo->proximo = NULL;

    Fila* alvo = (tipo == 'P' || tipo == 'p') ? fPrioritaria : fNormal;

    if (alvo->inicio == NULL) {
        alvo->inicio = novo;
        alvo->fim = novo;
    } else {
        alvo->fim->proximo = novo;
        alvo->fim = novo;
    }
}

void inserirTrabalho(Fila* fNormal, Fila* fPrioritaria) {
    int id, pags;
    char nomeArquivo[50];
    char tipo;

    id = gerarID(fNormal, fPrioritaria);

    printf("Nome do arquivo: ");
    scanf("%49s", nomeArquivo);

    printf("Paginas: ");
    scanf("%d", &pags);

    do {
        printf("Tipo (N/P): ");
        scanf(" %c", &tipo);
        if (!tipoValido(tipo)) {
            printf(COR_VERMELHA "Tipo invalido! Use N ou P.\n" COR_RESET);
        }
    } while (!tipoValido(tipo));

    inserirTrabalhoDireto(fNormal, fPrioritaria, id, nomeArquivo, pags, tipo);
    printf(COR_VERDE "Trabalho inserido na fila %c!\n" COR_RESET, tipo);
}

void processarTrabalho(Fila* fNormal, Fila* fPrioritaria) {
    NoFila* paraRemover = NULL;
    Fila* filaOrigem = NULL;

    if (fPrioritaria->inicio != NULL) {
        filaOrigem = fPrioritaria;
    } else if (fNormal->inicio != NULL) {
        filaOrigem = fNormal;
    } else {
        printf(COR_AMARELA "Nenhum trabalho na fila.\n" COR_RESET);
        return;
    }

    paraRemover = filaOrigem->inicio;
    printf(COR_AZUL "Processando: %s\n" COR_RESET, paraRemover->info.nomeArquivo);

    filaOrigem->inicio = paraRemover->proximo;
    if (filaOrigem->inicio == NULL) {
        filaOrigem->fim = NULL;
    }

    free(paraRemover);
}

void listardados_c(Fila* fNormal, Fila* fPrioritaria) {
    NoFila* atual;

    printf(COR_AZUL "\nFila Prioritaria:\n" COR_RESET);
    atual = fPrioritaria->inicio;
    if (atual == NULL) {
        printf("Fila vazia.\n");
    }
    while (atual != NULL) {
        printf("ID: %d | Arquivo: %s | Paginas: %d | Tipo: %c\n",
               atual->info.id, atual->info.nomeArquivo,
               atual->info.pags, atual->info.tipo);
        atual = atual->proximo;
    }

    printf(COR_AZUL "\nFila Normal:\n" COR_RESET);
    atual = fNormal->inicio;
    if (atual == NULL) {
        printf("Fila vazia.\n");
    }
    while (atual != NULL) {
        printf("ID: %d | Arquivo: %s | Paginas: %d | Tipo: %c\n",
               atual->info.id, atual->info.nomeArquivo,
               atual->info.pags, atual->info.tipo);
        atual = atual->proximo;
    }
}

void cancelarTrabalho(Fila* fNormal, Fila* fPrioritaria) {
    int id;
    printf("ID do trabalho a ser cancelado: ");
    scanf("%d", &id);

    Fila* filaOrigem = NULL;
    NoFila* atual = NULL;
    NoFila* anterior = NULL;

    filaOrigem = fPrioritaria;
    atual = filaOrigem->inicio;

    while (atual != NULL && atual->info.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        filaOrigem = fNormal;
        atual = filaOrigem->inicio;
        anterior = NULL;

        while (atual != NULL && atual->info.id != id) {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    if (atual == NULL) {
        printf(COR_AMARELA "Trabalho com ID %d nao encontrado.\n" COR_RESET, id);
        return;
    }

    if (anterior == NULL) {
        filaOrigem->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    if (atual == filaOrigem->fim) {
        filaOrigem->fim = anterior;
    }

    free(atual);
    printf(COR_VERMELHA "Trabalho com ID %d cancelado.\n" COR_RESET, id);
}

void salvarCSV(Fila* fNormal, Fila* fPrioritaria) {
    FILE* arquivo = fopen("dados_c.csv", "w");
    NoFila* atual;

    if (!arquivo) {
        printf(COR_VERMELHA "Erro ao abrir arquivo para salvar.\n" COR_RESET);
        return;
    }

    atual = fPrioritaria->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d,%s,%d,%c\n",
                atual->info.id, atual->info.nomeArquivo,
                atual->info.pags, atual->info.tipo);
        atual = atual->proximo;
    }

    atual = fNormal->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d,%s,%d,%c\n",
                atual->info.id, atual->info.nomeArquivo,
                atual->info.pags, atual->info.tipo);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf(COR_VERDE "dados_c salvos em dados_c.csv\n" COR_RESET);
}

void carregarCSV(Fila* fNormal, Fila* fPrioritaria) {
    FILE* arquivo = fopen("dados_c.csv", "r");
    char linha[256];

    if (!arquivo) {
        printf(COR_AMARELA "Arquivo dados_c.csv nao encontrado. Iniciando com filas vazias.\n" COR_RESET);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        int id, pags;
        char nomeArquivo[50], tipo;

        if (sscanf(linha, "%d,%49[^,],%d,%c", &id, nomeArquivo, &pags, &tipo) == 4) {
            inserirTrabalhoDireto(fNormal, fPrioritaria, id, nomeArquivo, pags, tipo);
        }
    }

    fclose(arquivo);
    printf(COR_VERDE "dados_c carregados do arquivo dados_c.csv\n" COR_RESET);
}

void liberarFila(Fila* f) {
    NoFila* atual = f->inicio;
    while (atual != NULL) {
        NoFila* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    f->inicio = NULL;
    f->fim = NULL;
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void exibirMenu() {
    limparTela();
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(COR_VERMELHA " IMPRESSORA - GERENCIAMENTO DE FILAS\n" COR_RESET);
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(" 1 - Inserir trabalho\n");
    printf(" 2 - Processar trabalho\n");
    printf(" 3 - Listar dados_c\n");
    printf(" 4 - Cancelar trabalho\n");
    printf(" 5 - Salvar e Sair\n");
    printf(" 6 - Carregar dados_c de arquivo\n");
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(" Escolha uma opcao: ");
}

void pausarTela() {
    int c;
    printf("\n[Pressione ENTER para continuar...]");
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}