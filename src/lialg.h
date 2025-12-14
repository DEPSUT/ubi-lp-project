/**
 * @file lialg.h
 * @brief Biblioteca de Álgebra Linear (@a Linear @a Algebra).
 * Define os Tipos Abstratos de Dados para Vetores e Matrizes,
 * bem como as funções para a sua manipulação, alocação dinâmica e cálculos.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.5
 */

#ifndef LIALG_H
#define LIALG_H

#include <stdlib.h>
#include <math.h>

#include "functions.h"

/**
 * @struct vector
 * @brief Estrutura que representa um @c array dinâmico de inteiros.
 */
typedef struct vector
{
    int *data; ///< Ponteiro para o @c array de dados do vetor.
    int size;  ///< Número de elementos.
} vector;

/**
 * @struct matrix
 * @brief Estrutura que representa uma matriz dinâmica.
 * Implementada como um vetor de ponteiros @c (int**) para permitir
 * sintaxe de acesso normal mat[i][j].
 */
typedef struct matrix
{
    int **data; ///< Vetor de ponteiros para as linhas.
    int rows;   ///< Número de linhas.
    int cols;   ///< Número de colunas.
} matrix;

/* --- Vetores --- */

/**
 * @brief Inicializa um vetor com alocação dinâmica.
 * @param vec Ponteiro para a estrutura a inicializar.
 * @param size Tamanho desejado para o vetor.
 * @warning Deve chamar @c vec_destroy() no fim para evitar @a memory @a leaks.
 */
void vec_init(vector *vec, int size);

/**
 * @brief Copia profundamente (@a Deep @a Copy) o conteúdo de um vetor para outro.
 * Aloca memória nova para o vetor de destino.
 * @param from Vetor de origem.
 * @param to Vetor de destino (será inicializado dentro da função).
 */
void vec_copy_from_to(vector *from, vector *to);

/**
 * @brief Lê valores inteiros do utilizador ou gera-os (dependendo de @c config.h).
 * Garante que os valores estão entre @c min e @c max.
 * @param vec Vetor onde guardar os dados.
 * @param min Valor mínimo aceitável.
 * @param max Valor máximo aceitável.
 */
void vec_read(vector *vec, int min, int max);

/**
 * @brief Imprime o vetor formatado no ecrã.
 * @param vec Vetor a imprimir.
 * @param trail Número de espaços para alinhamento  (@a padding).
 */
void vec_write(const vector *vec, const int trail);

/**
 * @brief Ordena o vetor por ordem crescente.
 * Implementa o algoritmo @a Insertion @a Sort.
 * @param vec Vetor a ordenar.
 */
void vec_sort_asc(vector *vec);

/**
 * @brief Liberta a memória alocada para o vetor.
 * @param vec Vetor a destruir.
 */
void vec_destroy(vector *vec);

/**
 * @brief Obtém o valor máximo do vetor.
 * @param vec Vetor a analisar.
 * @retval int O maior valor encontrado.
 */
int vec_get_max(const vector *vec);

/**
 * @brief Obtém o valor mínimo do vetor.
 * @param vec Vetor a analisar.
 * @retval int O menor valor encontrado.
 */
int vec_get_min(const vector *vec);

/**
 * @brief Calcula o Produto Externo entre dois vetores.
 * O resultado é uma matriz onde @c Mat[i][j] = @c vec1[i] * @c vec2[j].
 * @param mat Matriz de destino (será inicializada).
 * @param vec1 Primeiro vetor (linhas).
 * @param vec2 Segundo vetor (colunas).
 * @warning Não use @c mat_init() na matriz inserida antes de chamar esta função,
 * para não correr o risco de causar @a memory @a leaks.
 */
void vec_mult(matrix *mat, vector *vec1, vector *vec2);

/* --- Matrizes --- */

/**
 * @brief Inicializa uma matriz dinâmica.
 * Aloca memória para o @c array de linhas e para cada linha individualmente.
 * @param mat Ponteiro para a matriz.
 * @param cols Número de colunas.
 * @param rows Número de linhas.
 * @warning Deve chamar @c mat_destroy() no fim para evitar @a memory @a leaks.
 */
void mat_init(matrix *mat, int cols, int rows);

/**
 * @brief Imprime a matriz formatada.
 * @param mat Matriz a imprimir.
 * @param trail Espaçamento para alinhamento.
 */
void mat_write(const matrix *mat, int trail);

/**
 * @brief Calcula o determinante da matriz.
 * Utiliza o algoritmo de Eliminação de @a Gauss com Pivotagem Parcial.
 * @param mat Matriz a analisar.
 * @retval double O valor do determinante.
 */
double mat_get_determinant(matrix *mat);

/**
 * @brief Liberta toda a memória associada à matriz.
 * Liberta cada linha e depois o @c array de ponteiros principal.
 * @param mat Matriz a destruir.
 */
void mat_destroy(matrix *mat);

#endif
