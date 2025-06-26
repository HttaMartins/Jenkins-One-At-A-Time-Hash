#include "jenkins.h" // Inclui a nossa biblioteca de tabela hash

int main() {
    // Inicializa a tabela hash no início do programa
    iniciaTabelaHash();

    char input[MAX_KEY_LENGTH];
    int choice;

    do {
        printf("\n --------------------------\n");
        printf("\nMenu da Tabela Hash:\n");
        printf("1. Inserir nome\n");
        printf("2. Buscar nome\n");
        printf("3. Remover nome\n");
        printf("4. Exibir tabela\n");
        printf("5. Exibir estatisticas\n");
        printf("0. Sair\n");
        printf("\n --------------------------\n");
        printf("Escolha uma opcao: ");
        
        // Lê a entrada do usuário de forma segura
        if (scanf("%d", &choice) != 1) {
            choice = -1; // Força uma opção inválida em caso de erro
        }
        // Limpa o buffer de entrada para evitar problemas com leituras futuras
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                printf("Digite o nome a ser inserido: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // Remove o '\n'
                inserir(input);
                break;
            case 2:
                printf("Digite o nome a ser buscado: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                if ( Busca(input)) {
                    printf("'%s' encontrado na tabela.\n", input);
                } else {
                    printf("'%s' nao encontrado na tabela.\n", input);
                }
                break;
            case 3:
                printf("Digite o nome a ser removido: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                remover(input);
                break;
            case 4:
                imprimir_tabela();
                break;
            case 5:
                estatisticas();
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (choice != 0);
    
    // Exibe as estatísticas finais antes de sair
    estatisticas();

    // Libera toda a memória alocada
    liberar_tabela();

    return 0;
}
