#include "triagem.h"


// 1. FUNÇÕES UTILITÁRIAS E MULTIPLATAFORMA
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausarTela() {
    printf("\n[Pressione ENTER para continuar...]");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

int contarPacientes(No* inicio) {
    int cont = 0;
    No* atual = inicio;
    while (atual != NULL) {
        cont++;
        atual = atual->proximo;
    }
    return cont;
}

int senhaExiste(No* inicio, int senhaBusca) {
    No* atual = inicio;
    while (atual != NULL) {
        if (atual->dados.senha == senhaBusca) return 1;
        atual = atual->proximo;
    }
    return 0;
}

void exibirMenu(No* inicio) {
    limparTela();
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(COR_VERMELHA "       HOSPITAL - TRIAGEM (A3)\n" COR_RESET);
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(" Pacientes aguardando: %d\n\n", contarPacientes(inicio));
    
    printf(" 1 - Cadastrar novo paciente\n");
    printf(" 2 - Buscar paciente por senha\n");
    printf(" 3 - Editar paciente\n");
    printf(" 4 - Excluir/Atender paciente\n");
    printf(" 5 - Listar fila de triagem\n");
    printf(" 0 - Salvar e Sair\n");
    printf(COR_AMARELA "========================================\n" COR_RESET);
    printf(" Escolha uma opcao: ");
}

// 2. FUNÇÕES PRINCIPAIS 
void inserirOrdenado(No** inicio) {
    limparTela();
    printf(COR_VERMELHA "--- CADASTRAR PACIENTE ---\n\n" COR_RESET);

    // Alocação dinâmica do novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memoria!\n");
        pausarTela();
        return;
    }

    // Leitura e validação da senha (deve ser única)
    printf("Digite a senha do paciente (Apenas numeros): ");
    scanf("%d", &novoNo->dados.senha);
    if (senhaExiste(*inicio, novoNo->dados.senha)) {
        printf(COR_AMARELA "\nErro: A senha %d ja esta cadastrada!\n" COR_RESET, novoNo->dados.senha);
        free(novoNo);
        pausarTela();
        return;
    }

    // Limpa o buffer do teclado antes de ler a string
    int c; while ((c = getchar()) != '\n' && c != EOF);

    printf("Nome do paciente: ");
    fgets(novoNo->dados.nome, sizeof(novoNo->dados.nome), stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0'; 

    printf("Idade: ");
    scanf("%d", &novoNo->dados.idade);

    // Validação obrigatória da gravidade (1 a 4)
    do {
        printf("Gravidade (1=Emergencia, 2=Urgencia, 3=Pouco Urgente, 4=Nao Urgente): ");
        scanf("%d", &novoNo->dados.gravidade);
        if (novoNo->dados.gravidade < 1 || novoNo->dados.gravidade > 4) {
            printf(COR_AMARELA "Valor invalido! A gravidade deve ser entre 1 e 4.\n" COR_RESET);
        }
    } while (novoNo->dados.gravidade < 1 || novoNo->dados.gravidade > 4);

    novoNo->proximo = NULL;

    // LÓGICA DE INSERÇÃO ORDENADA (Gravidade -> Senha)
    if (*inicio == NULL) {
        *inicio = novoNo; 
    } else {
        No* atual = *inicio;
        No* anterior = NULL;

        // Encontra a posição correta
        while (atual != NULL) {
            // Se a gravidade do novo for menor (mais grave), ou se for igual mas a senha for menor
            if (novoNo->dados.gravidade < atual->dados.gravidade || 
               (novoNo->dados.gravidade == atual->dados.gravidade && novoNo->dados.senha < atual->dados.senha)) {
                break;
            }
            anterior = atual;
            atual = atual->proximo;
        }

        if (anterior == NULL) {
            // Insere no início
            novoNo->proximo = *inicio;
            *inicio = novoNo;
        } else {
            // Insere no meio ou no fim
            novoNo->proximo = atual;
            anterior->proximo = novoNo;
        }
    }

    printf(COR_VERDE "\nPaciente cadastrado e inserido na fila com sucesso!\n" COR_RESET);
    pausarTela();
}

void listarPacientes(No* inicio) {
    limparTela();
    printf(COR_VERMELHA "--- FILA DE TRIAGEM ---\n\n" COR_RESET);

    if (inicio == NULL) {
        printf("A fila esta vazia no momento.\n");
    } else {
        No* atual = inicio;
        printf("%-10s | %-20s | %-5s | %-10s\n", "SENHA", "NOME", "IDADE", "GRAVIDADE");
        printf("----------------------------------------------------------\n");
        
        while (atual != NULL) {
            printf("%-10d | %-20s | %-5d | %-10d\n", 
                atual->dados.senha, atual->dados.nome, atual->dados.idade, atual->dados.gravidade);
            atual = atual->proximo;
        }
    }
    pausarTela();
}

void buscarPaciente(No* inicio) {
    limparTela();
    printf(COR_VERMELHA "--- BUSCAR PACIENTE ---\n\n" COR_RESET);

    if (inicio == NULL) {
        printf("A fila esta vazia.\n");
        pausarTela();
        return;
    }

    int senhaBusca;
    printf("Digite a senha para busca: ");
    scanf("%d", &senhaBusca);

    No* atual = inicio;
    int encontrou = 0;

    while (atual != NULL) {
        if (atual->dados.senha == senhaBusca) {
            printf(COR_VERDE "\nPaciente Encontrado!\n" COR_RESET);
            printf("Nome: %s\n", atual->dados.nome);
            printf("Idade: %d\n", atual->dados.idade);
            printf("Gravidade: %d\n", atual->dados.gravidade);
            encontrou = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrou) {
        printf(COR_AMARELA "\nPaciente com a senha %d nao encontrado.\n" COR_RESET, senhaBusca);
    }
    pausarTela();
}

void editarPaciente(No* inicio) {
    limparTela();
    printf(COR_VERMELHA "--- EDITAR PACIENTE ---\n\n" COR_RESET);

    if (inicio == NULL) {
        printf("A fila esta vazia.\n");
        pausarTela();
        return;
    }

    int senhaBusca;
    printf("Digite a senha do paciente que deseja editar: ");
    scanf("%d", &senhaBusca);

    No* atual = inicio;
    while (atual != NULL) {
        if (atual->dados.senha == senhaBusca) {
            printf("\nEditando paciente: %s\n", atual->dados.nome);
            
            int c; while ((c = getchar()) != '\n' && c != EOF);

            printf("Novo nome: ");
            fgets(atual->dados.nome, sizeof(atual->dados.nome), stdin);
            atual->dados.nome[strcspn(atual->dados.nome, "\n")] = '\0';

            printf("Nova idade: ");
            scanf("%d", &atual->dados.idade);
            
            printf(COR_VERDE "\nDados atualizados com sucesso!\n" COR_RESET);
            pausarTela();
            return;
        }
        atual = atual->proximo;
    }

    printf(COR_AMARELA "\nPaciente com a senha %d nao encontrado.\n" COR_RESET, senhaBusca);
    pausarTela();
}

void atenderPaciente(No** inicio) {
    limparTela();
    printf(COR_VERMELHA "--- EXCLUIR / ATENDER PACIENTE ---\n\n" COR_RESET);

    if (*inicio == NULL) {
        printf("Nenhum paciente na fila para atender.\n");
        pausarTela();
        return;
    }

    int senhaBusca;
    printf("Digite a senha do paciente a ser removido: ");
    scanf("%d", &senhaBusca);

    No* atual = *inicio;
    No* anterior = NULL;

    while (atual != NULL && atual->dados.senha != senhaBusca) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf(COR_AMARELA "\nPaciente com a senha %d nao encontrado.\n" COR_RESET, senhaBusca);
        pausarTela();
        return;
    }

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    printf(COR_VERDE "\nPaciente %s (Senha: %d) removido/atendido com sucesso!\n" COR_RESET, atual->dados.nome, atual->dados.senha);
    free(atual); 
    pausarTela();
}

// 3. FUNÇÕES DE PERSISTÊNCIA E MEMÓRIA
void salvarCSV(No* inicio) {
    FILE* arquivo = fopen("dados_a.csv", "w");
    if (arquivo == NULL) {
        printf(COR_AMARELA "Erro ao abrir o arquivo para salvar!\n" COR_RESET);
        return;
    }

    // Grava o cabeçalho obrigatório (separador ;)
    fprintf(arquivo, "senha;nome;idade;gravidade\n");

    No* atual = inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d;%s;%d;%d\n", 
            atual->dados.senha, atual->dados.nome, atual->dados.idade, atual->dados.gravidade);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf(COR_VERDE "Dados salvos com sucesso em 'dados_a.csv'.\n" COR_RESET);
}

void carregarCSV(No** inicio) {
    FILE* arquivo = fopen("dados_a.csv", "r");
    if (arquivo == NULL) {

        return; 
    }

    char linha[200];
    int primeiraLinha = 1;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (primeiraLinha) {
            primeiraLinha = 0;
            continue;
        }

        linha[strcspn(linha, "\n")] = '\0';
        char* token = strtok(linha, ";");
        if (token == NULL) continue;

        No* novoNo = (No*)malloc(sizeof(No));
        if (novoNo == NULL) break;

        novoNo->dados.senha = atoi(token);
        
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(novoNo->dados.nome, token);
        
        token = strtok(NULL, ";");
        if (token != NULL) novoNo->dados.idade = atoi(token);
        
        token = strtok(NULL, ";");
        if (token != NULL) novoNo->dados.gravidade = atoi(token);

        novoNo->proximo = NULL;

        // Re-insere de forma ordenada 
        if (*inicio == NULL) {
            *inicio = novoNo;
        } else {
            No* atual = *inicio;
            No* anterior = NULL;
            while (atual != NULL) {
                if (novoNo->dados.gravidade < atual->dados.gravidade || 
                   (novoNo->dados.gravidade == atual->dados.gravidade && novoNo->dados.senha < atual->dados.senha)) {
                    break;
                }
                anterior = atual;
                atual = atual->proximo;
            }
            if (anterior == NULL) {
                novoNo->proximo = *inicio;
                *inicio = novoNo;
            } else {
                novoNo->proximo = atual;
                anterior->proximo = novoNo;
            }
        }
    }
    fclose(arquivo);
}

void liberarLista(No** inicio) {
    No* atual = *inicio;
    No* proximo = NULL;

    while (atual != NULL) {
        proximo = atual->proximo; 
        free(atual);              
        atual = proximo;          
    }
    *inicio = NULL;
}