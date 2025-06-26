#ifndef JENKINS_H
#define JENKINS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes e Definições de Tipo ---

#define TABLE_SIZE 10
#define MAX_KEY_LENGTH 100

typedef struct Node {
    char key[MAX_KEY_LENGTH];
    struct Node *next;
} Node;

// --- Protótipos das Funções Públicas ---

/**
 * @brief Inicializa a tabela hash e zera as estatísticas.
 * Deve ser chamado no início do programa.
 */
void iniciaTabelaHash();

/**
 * @brief Insere um novo elemento na tabela e atualiza as estatísticas de colisão.
 * @param key A chave a ser inserida.
 */
void inserir(const char *key);

/**
 * @brief Busca por um elemento, medindo o tempo e os passos necessários.
 * @param key A chave a ser buscada.
 * @return Ponteiro para o nó se encontrado, caso contrário NULL.
 */
Node* Busca(const char *key);

/**
 * @brief Remove um elemento da tabela.
 * @param key A chave a ser removida.
 */
void remover(const char *key);

/**
 * @brief Exibe o conteúdo atual de toda a tabela hash.
 */
void imprimir_tabela();

/**
 * @brief Exibe as estatísticas de desempenho coletadas.
 */
void estatisticas();

/**
 * @brief Libera toda a memória alocada dinamicamente pela tabela.
 */
void liberar_tabela();

#endif // JENKINS_H
