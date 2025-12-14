/**
 * @file config.h
 * @brief Ficheiro de configuração global do projeto.
 * Contém constantes que definem o comportamento
 * da compilação, tamanhos de estruturas e limites numéricos.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.0
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief _Flag_ de depuração e testes.
 * * Se definido como `1`:
 * - Os vetores são gerados aleatoriamente (poupa tempo na inserção manual).
 * - O menu apresenta a opção extra "10 - Gerar novos números".
 * - Inclui a biblioteca `<time.h>` e usa `srand()`.
 */
#define DEBUGGING_ENABLED 1

/**
 * @brief Número de itens a apresentar por página no menu.
 * Controla a paginação automática da interface.
 */
#define ITEMS_PER_PAGE 7

#define TAM 20  ///< Tamanho fixo para alocação inicial dos vetores.
#define MIN -3  ///< Limite inferior para a geração ou leitura de valores.
#define MAX 18  ///< Limite superior para a geração ou leitura de valores.

#endif