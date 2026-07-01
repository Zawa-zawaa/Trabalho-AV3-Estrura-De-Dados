#include "emergencia.h"



int main() {
    FILE* arquivo = fopen("dados_b.csv", "r");
    // contagem de dados e alocacao dinamica
    int quant = contarRegistros(arquivo);
    // o topo da pilha e quant-1 = 11
    fclose(arquivo);
    ChamadaEmergencia* Chamadas = malloc(quant * sizeof(ChamadaEmergencia));
    if (Chamadas == NULL) {
        printf("Erro de memória.\n");
        return 1;
    }

    lercsv(Chamadas);  // faz a leitura dos dados pra struct na memoria

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
                registrarChamada(&Chamadas,&quant);
                pausarTela();
                break;


            case 2:  // consultar ultima chamada
                consultarUltimaChamada(Chamadas,quant);
                pausarTela();
                break;


            case 3:  // atender chamada (excluir)


                break;

            case 4:  // listar todas as chamadas
                listarChamadas(Chamadas, quant);
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



    } while (inputUser);


    free(Chamadas);
    return 0;
}
