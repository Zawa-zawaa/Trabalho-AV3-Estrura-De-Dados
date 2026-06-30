#include "triagem.h"

int main() {
    // Configura o terminal para exibir acentuação corretamente
    setlocale(LC_ALL, "Portuguese");

    // O ponteiro 'inicio' é o cabeça da nossa lista encadeada
    No* inicio = NULL;

    // Tenta carregar o arquivo CSV automaticamente ao iniciar
    carregarCSV(&inicio);

    int opcao;

    do {
        exibirMenu(inicio);
        
        // Lê a opção do usuário
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer se o usuário digitar uma letra por engano
            int c; while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; 
        }

        switch(opcao) {
            case 1:
                inserirOrdenado(&inicio);
                break;
            case 2:
                buscarPaciente(inicio);
                break;
            case 3:
                editarPaciente(inicio);
                break;
            case 4:
                atenderPaciente(&inicio);
                break;
            case 5:
                listarPacientes(inicio);
                break;
            case 0:
                // Antes de sair, salva no CSV e libera a memória dinâmica
                salvarCSV(inicio);
                liberarLista(&inicio);
                printf(COR_VERDE "\nSistema encerrado com seguranca. Ate logo!\n" COR_RESET);
                break;
            default:
                printf(COR_AMARELA "\nOpcao invalida! Tente novamente.\n" COR_RESET);
                pausarTela();
        }
    } while(opcao != 0);

    return 0;
}