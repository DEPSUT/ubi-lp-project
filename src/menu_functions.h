/**
 * @file menu_functions.h
 * @brief Controlador da lógica de negócio e definição do menu.
 * Contém a estrutura de dados que define cada item do menu e liga
 * a interface de texto às funções lógicas da biblioteca @c lialg.h.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.0
 */

#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H

#include <math.h>

#include "lialg.h"
#include "functions.h"
#include "config.h"

/**
 * @struct menuItem
 * @brief Define uma opção individual do menu.
 * Utiliza o padrão "@a Dispatch @a Table" (Ponteiros para funções) para evitar
 * estruturas @c switch gigantes.
 */
typedef struct menuItem
{
    const char *title; ///< O título curto da opção, visível na lista principal.
    const char *help;  ///< Descrição detalhada apresentada no menu de ajuda.
    /**
     * @brief Ponteiro para a função a executar (@a Callback).
     * @param vec Ponteiro @c void genérico (normalmente @a cast para @c vector*).
     */
    void (*action)(void *vec);
    const int useVector; ///< @a Flag: @c 1 se a função requer o vetor principal, @c 0 caso contrário.
} menuItem;

/**
 * @brief @c array constante contendo todas as opções do menu.
 * Definido em @c menu_functions.c.
 */
extern const menuItem menu[];

/**
 * @brief Número total de elementos presentes na @c array @c menu[]
 */
extern const int TOTAL_ITEMS;

/**
 * @brief Número total de páginas tendo em conta @c ITEMS_PER_PAGE definido em @c config.h
 */
extern const int TOTAL_PAGES;

#if DEBUGGING_ENABLED
/**
 * @brief Preenche o vetor com números aleatórios.
 * Função utilitária disponível apenas em modo de @a debug para facilitar
 * testes rápidos sem necessidade de inserção manual de dados.
 * @param vec Ponteiro para o vetor a preencher.
 */
void generateRandomVector(vector *vec);
#endif

/**
 * @brief Calcula o espaçamento necessário para formatação visual (@a padding).
 * Analisa o número de dígitos do maior e menor valor do vetor para
 * determinar a largura da coluna na impressão de tabelas.
 * @param vec Ponteiro para o vetor a analisar.
 * @retval int O número de caracteres de largura.
 */
int getTrail(vector *vec);

/**
 * @name Callbacks do Menu
 * Conjunto de funções executadas quando o utilizador seleciona uma opção.
 * Recebem um ponteiro @c void* para manter a assinatura genérica da @c struct @c menuItem.
 * @{
 */

/** @brief Encontra e apresenta o valor máximo. */
void menu_max(void *_vec);

/** @brief Calcula e apresenta o seno de cada elemento. */
void menu_sin(void *_vec);

/** @brief Filtra e apresenta apenas os elementos divisíveis por 3. */
void menu_div_3(void *_vec);

/** @brief Cria e apresenta uma matriz comparativa (Original vs Ordenado). */
void menu_sorted_matrix(void *_vec);

/** @brief Multiplica escalarmente o vetor por 3 e apresenta o resultado. */
void menu_mult_3(void *_vec);

/** @brief Apresenta o vetor ordenado (sem alterar o original permanentemente). */
void menu_sorted_vector(void *_vec);

/** @brief Pede um segundo vetor e calcula a soma linear (@c Vec1 + 2 * @c Vec2). */
void menu_sum_second_vector(void *_vec);

/** @brief Calcula e apresenta a decomposição em fatores primos de cada elemento. */
void menu_prime_decomposition(void *_vec);

/**
 * @brief Gera uma matriz 20x20 através do produto de vetores.
 * @note O resultado é guardado numa variável estática interna para uso posterior.
 */
void menu_matrix_20x20(void *_vec);

/** @brief Apresenta o sistema de ajuda paginado com descrições detalhadas. */
void menu_help_page(void *_vec);

/**
 * @brief Calcula o determinante da matriz gerada anteriormente.
 * @warning Requer que a função @c menu_matrix_20x20() tenha sido executada previamente.
 */
void menu_matrix_determinant(void *_);

/** @} */ // Fim do grupo Callbacks

/**
 * @brief Limpa os recursos internos do módulo de menu.
 * Deve ser chamada antes do programa terminar para libertar a memória
 * da matriz estática (se esta tiver sido inicializada).
 */
void menu_destroy();

/**
 * @brief Renderiza a interface do menu e processa a paginação.
 * Responsável por desenhar as opções no ecrã e ler a escolha do utilizador.
 * @param page Índice da página atual (@c 0 a @c TOTAL_PAGES - @c 1).
 * @param option Ponteiro onde será guardada a opção escolhida pelo utilizador.
 * @retval int O índice (@a offset) do primeiro item mostrado na página atual.
 */
int menu_show(int page, int *option);

#endif