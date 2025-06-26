#include "jenkins.h"

// --- Variáveis Globais Estáticas ---
static Node* tabela_hash[TABLE_SIZE];
static total_elementos = 0;
static int total_colisoes = 0;
static int total_buscas = 0;
static double tempo_total_busca = 0.0;
// ------------------------------------

// Função de Hash
static  int jenkins_one_at_a_time_hash(const char *key) {
     int hash = 0; //inicializa em 0, não é modificada pela função
    while (*key) {
        hash += *key++; // pega o valor do caractere e soma a hash
        hash += (hash << 10); // multiplica a hash por 2^10 e soma a hash
        hash ^= (hash >> 6); // faz um XOR com a hash deslocada 6 bits para a direita e soma a hash
    }
    // Emabaralhamento final
    hash += (hash << 3);  // multiplica a hash por 2^3 e soma a hash
    hash ^= (hash >> 11); // faz um XOR com a hash deslocada 11 bits para a direita e soma a hash
    hash += (hash << 15); // multiplica a hash por 2^15 e soma a hash
    return hash % TABLE_SIZE; // divide hasg por tamanho da tabela e retorna o resto
}

void iniciaTabelaHash() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela_hash[i] = NULL;
    }
    total_elementos = 0; // inicializa a quantidade de elementos
    total_colisoes = 0; // inicializa a quantidade de colisões
    total_buscas = 0; // inicializa a quantidade de buscas
    tempo_total_busca = 0.0; // inicializa o tempo total de busca
}

void inserir(const char *key) {
    Node *newNode = (Node*) malloc(sizeof(Node)); // aloca memória para o novo nó
    if (newNode == NULL) {
        printf("Erro: Nao foi possivel alocar memoria.\n");
        return;
    }
    
    strncpy(newNode->key, key, MAX_KEY_LENGTH - 1);
    newNode->key[MAX_KEY_LENGTH - 1] = '\0';
    
    int index = jenkins_one_at_a_time_hash(key);

    if (tabela_hash[index] != NULL) {
        total_colisoes++;
        printf("Colisao detectada na posicao [%d].\n", index);
    }
    
    newNode->next = tabela_hash[index];
    tabela_hash[index] = newNode;
    total_elementos++;
    printf("'%s' inserido na posicao [%d].\n", key, index);
}

Node* Busca(const char *key) {
    clock_t start = clock(); // inicia o temporizador
    int index = jenkins_one_at_a_time_hash(key); // calcula o índice da chave
    Node *current = tabela_hash[index]; // aponta para o nó atual
    int steps = 0; // contador de passos

    while (current != NULL) {
        steps++;
        if (strcmp(current->key, key) == 0) {
            clock_t end = clock();
            tempo_total_busca += ((double) (end - start)) / CLOCKS_PER_SEC;
            total_buscas++;
            printf("Busca por '%s' levou %d passo(s).\n", key, steps);
            return current;
        }
        current = current->next;
    }

    clock_t end = clock();
    tempo_total_busca += ((double) (end - start)) / CLOCKS_PER_SEC;
    total_buscas++;
    printf("Busca por '%s' levou %d passo(s) (nao encontrado).\n", key, steps);
    return NULL;
}

void remover(const char *key) {
    int index = jenkins_one_at_a_time_hash(key);
    Node *current = tabela_hash[index];
    Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) tabela_hash[index] = current->next;
            else prev->next = current->next;
            free(current);
            total_elementos--;
            printf("'%s' removido da posicao [%d].\n", key, index);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("'%s' nao encontrado para remocao.\n", key);
}

void imprimir_tabela() {
    printf("\n--- Conteudo da Tabela Hash ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node *current = tabela_hash[i];
        while (current != NULL) {
            printf("%s -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("-------------------------------\n");
}

void liberar_tabela() {
    for (int i = 0; i < TABLE_SIZE; i++) { 
        Node *current = tabela_hash[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        tabela_hash[i] = NULL;
    }
    printf("\nMemoria da tabela liberada.\n");
}

void estatisticas() {
    printf("\n--- Estatisticas de Desempenho ---\n");
    printf("Total de Elementos na Tabela: %d\n", total_elementos);
    printf("Total de Colisoes na Insercao: %d\n", total_colisoes);

    if (total_elementos > 1) { // A taxa só faz sentido com mais de 1 elemento
        double collision_rate = ((double)total_colisoes / (total_elementos - 1)) * 100.0; // Taxa de colisão
        printf("Taxa de Colisao: %.2f%%\n", collision_rate); // Taxa de colisão
    }
    
    printf("\nTotal de Buscas Realizadas: %d\n", total_buscas); //
    if (total_buscas > 0) { // A taxa só faz sentido com mais de 0 buscas
        double avg_search_time = (tempo_total_busca / total_buscas) * 1000.0; // Tempo médio de busca
        printf("Tempo Medio por Busca: %.6f ms\n", avg_search_time);
    }
    printf("----------------------------------\n");
}
