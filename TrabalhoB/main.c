#include "emergencia.h"



int main() {
    setlocale(LC_ALL, "portuguese");
    // abertura do arquivo
    FILE* arquivo = fopen("dados_b.csv", "r");
    // contagem de dados e alocacao dinamica
    int quant;
    if (arquivo == NULL) {
        quant = 0;
    } else {
        quant = contarRegistros(arquivo);
        fclose(arquivo);
    }
    ChamadaEmergencia* Chamadas = NULL;
    // o topo da pilha e quant-1
    if (quant > 0) {
        Chamadas = malloc(quant * sizeof(ChamadaEmergencia));
        if (Chamadas == NULL) {
            printf("Erro de memória.\n");
            return 1;
        }
        lercsv(Chamadas);  // faz a leitura dos dados pra struct na memoria
    }


    // LOOP PRINCIPAL
    int inputUser;
    do {
        exibirMenu();
        if (scanf("%d", &inputUser) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            inputUser = -1;
        }
        switch (inputUser) {
            case 1:  // registrar chamada
                registrarChamada(&Chamadas, &quant);
                pausarTela();
                break;


            case 2:  // consultar ultima chamada
                consultarUltimaChamada(Chamadas, quant);
                pausarTela();
                break;


            case 3:  // atender chamada (excluir)
                atenderChamada(&Chamadas,&quant);
                pausarTela();
                break;

            case 4:  // listar todas as chamadas
                listarChamadas(Chamadas, quant);
                printf("\nQuantidade de registros: %d",quant);
                pausarTela();


                break;

            case 5: // Buscar chamada por protocolo

                buscarChamada(Chamadas,quant);
                pausarTela();

            break;
            case 0:
                // Antes de sair, salva no CSV e libera a memória dinâmica
                printf(COR_VERDE "\nSistema encerrado com seguranca. Ate logo!\n" COR_RESET);
                break;
            default:
                printf(COR_AMARELA "\nOpcao invalida! Tente novamente.\n" COR_RESET);
                pausarTela();
        }



    } while (inputUser != 0);


    free(Chamadas);
    return 0;
}
