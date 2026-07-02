#include "fila.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    Fila fNormal, fPrioritaria;
    int opcao;

    inicializarFila(&fNormal);
    inicializarFila(&fPrioritaria);

    carregarCSV(&fNormal, &fPrioritaria);

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirTrabalho(&fNormal, &fPrioritaria);
                break;
            case 2:
                processarTrabalho(&fNormal, &fPrioritaria);
                break;
            case 3:
                listardados_c(&fNormal, &fPrioritaria);
                break;
            case 4:
                cancelarTrabalho(&fNormal, &fPrioritaria);
                break;
            case 5:
                salvarCSV(&fNormal, &fPrioritaria);
                liberarFila(&fNormal);
                liberarFila(&fPrioritaria);
                printf(COR_VERDE "Saindo do programa...\n" COR_RESET);
                break;
            case 6:
                liberarFila(&fNormal);
                liberarFila(&fPrioritaria);
                inicializarFila(&fNormal);
                inicializarFila(&fPrioritaria);
                carregarCSV(&fNormal, &fPrioritaria);
                break;
            default:
                printf(COR_AMARELA "Opcao invalida! Tente novamente.\n" COR_RESET);
        }

        if (opcao != 5) {
            pausarTela();
        }

    } while (opcao != 5);

    return 0;
}