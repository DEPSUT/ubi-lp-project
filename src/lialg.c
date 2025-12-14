/**
 * @file lialg.c
 * @brief Biblioteca de Álgebra Linear (@a Linear @a Algebra).
 * Define os Tipos Abstratos de Dados para Vetores e Matrizes,
 * bem como as funções para a sua manipulação, alocação dinâmica e cálculos.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.5
 */

#include "lialg.h"

/**
 * @brief Verifica se a alocação de memória foi bem sucedida.
 * Termina o programa se o ponteiro for @c NULL.
 * @param ptr Ponteiro retornado pelo @c malloc().
 */
void checkForMallocErr(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Erro fatal: Falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
}


/* --- Vetores --- */


void vec_init(vector *vec, int size)
{
    vec->size = size;
    vec->data = (int *)malloc(vec->size * sizeof(int));

    checkForMallocErr(vec->data);
}

void vec_destroy(vector *vec)
{
    free(vec->data);
}

void vec_copy_from_to(vector *from, vector *to)
{
    to->size = from->size;
    to->data = (int *)malloc(sizeof(int) * to->size);
    for (int i = 0; i < to->size; i++)
        to->data[i] = from->data[i];
}

void vec_read(vector *vec, int min, int max)
{
    int temp = lines;
    for (int i = 0; i < vec->size; i++)
    {
        lines = 0;
        print("Insira o %dº número: ", i + 1);
        scan("%d", &vec->data[i]);
        clearOutput();
        if (vec->data[i] < min || vec->data[i] > max)
            i--;
    }
    lines = temp;
}

void vec_write(const vector *vec, const int trail)
{
    print("[");
    for (int i = 0; i < vec->size - 1; i++)
        print("%*d, ", trail, vec->data[i]);
    print("%*d]\n", trail, vec->data[vec->size - 1]);
}

void vec_sort_asc(vector *vec)
{
    int *data = vec->data;
    for (int i = 0; i < vec->size - 1; i++)
        if (data[i] > data[i + 1])
        {
            int temp = data[i + 1];
            data[i + 1] = data[i];
            data[i] = temp;
            for (int k = i; k > 0 && data[k] < data[k - 1]; k--)
            {
                temp = data[k - 1];
                data[k - 1] = data[k];
                data[k] = temp;
            }
        }
}

int vec_get_max(const vector *vec)
{
    int max = vec->data[0];
    for (int i = 1; i < vec->size; i++)
        if (vec->data[i] > max)
            max = vec->data[i];
    return max;
}

int vec_get_min(const vector *vec)
{
    int min = vec->data[0];
    for (int i = 1; i < vec->size; i++)
        if (vec->data[i] < min)
            min = vec->data[i];
    return min;
}

void vec_mult(matrix *mat, vector *vec1, vector *vec2)
{
    mat_init(mat, vec1->size, vec2->size);
    for (int i = 0; i < mat->rows; i++)
        for (int k = 0; k < mat->cols; k++)
            mat->data[i][k] = vec1->data[i] * vec2->data[k];
}


/* --- Matrizes --- */


void mat_init(matrix *mat, int cols, int rows)
{
    mat->cols = cols;
    mat->rows = rows;
    mat->data = (int **)malloc(mat->rows * sizeof(int *));
    checkForMallocErr(mat->data);
    for (int i = 0; i < mat->rows; i++)
    {
        mat->data[i] = (int *)malloc(mat->cols * sizeof(int));
        checkForMallocErr(mat->data[i]);
    }
}

void mat_write(const matrix *mat, int trail)
{
    for (int i = 0; i < mat->rows; i++)
    {
        print("[");
        for (int k = 0; k < mat->cols - 1; k++)
            print("%*d, ", trail, mat->data[i][k]);
        print("%*d]\n", trail, mat->data[i][mat->cols - 1]);
    }
}

/**
 * @brief Calcula o determinante utilizando Eliminação de @a Gauss com Pivotagem Parcial.
 * * O algoritmo transforma a matriz numa Matriz Triangular Superior.
 * O determinante é o produto da diagonal principal (ajustado pelo sinal das trocas de linhas).
 * * @par Algoritmo:
 * _Gaussian Elimination with Partial Pivoting._
 * * @par Referência:
 * _Press, W. H., et al. (1992). Numerical Recipes in C. Cambridge Univ. Press._
 * * @param mat A matriz original (preservada através de cópia interna).
 * @retval double O determinante. Retorna 0 se a matriz não for quadrada.
 * * @par Complexidade:
 * O(N^3) - Cúbico. Essencial para processar matrizes grandes (ex: 20x20) em tempo útil.
 */
double mat_get_determinant(matrix *mat)
{
    if (mat->cols != mat->rows)
        return 0;

    int n = mat->rows;
    double det = 1.0;

    // Cópia da matriz temporária em double
    double **temp = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        temp[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = (double)mat->data[i][j];
        }
    }

    // Eliminação de Gauss (Triangularização)
    for (int i = 0; i < n; i++)
    {
        // Pivotagem: Encontrar o maior valor na coluna para estabilidade
        int pivot = i;
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
                pivot = j;
        }

        // Trocar linhas se o pivot não for a linha atual
        if (pivot != i)
        {
            double *swap = temp[i];
            temp[i] = temp[pivot];
            temp[pivot] = swap;
            det *= -1.0; // Trocar linhas inverte o sinal do determinante
        }

        // Se o pivot for zero, a matriz é singular
        if (fabs(temp[i][i]) < 1e-9)
        {
            det = 0;
            // Se encontrámos um zero na diagonal principal, acabou.
            break;
        }

        // Eliminar os elementos abaixo do pivot
        for (int j = i + 1; j < n; j++)
        {
            double factor = temp[j][i] / temp[i][i];
            for (int k = i; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }
    }

    // Calcular o produto da diagonal principal
    if (det != 0)
        for (int i = 0; i < n; i++)
            det *= temp[i][i];

    for (int i = 0; i < n; i++)
        free(temp[i]);
    free(temp);

    return det;
}

void mat_destroy(matrix *mat)
{
    for (int i = 0; i < mat->rows; i++)
        free(mat->data[i]);
    free(mat->data);
}
