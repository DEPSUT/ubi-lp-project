#include "lialg.h"

/*
 *
 * Vectors
 *
 */

void vec_init(vector *vec, int size)
{
    vec->size = size;
    vec->data = (int *)malloc(vec->size * sizeof(int));
}

// void vec_resize(vector *vec, size_t size)
// {
//     vec->size = size;
//     vec->data = (int *)realloc(vec->data, vec->size * sizeof(int));
// }

// void vec_push(vector *vec, int value)
// {
//     vec->size++;
//     vec->data = (int *)realloc(vec->data, vec->size * sizeof(int));
//     vec->data[vec->size - 1] = value;
// }

// void vec_pop(vector *vec)
// {
//     vec->size--;
//     vec->data = (int *)realloc(vec->data, vec->size * sizeof(int));
// }

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
    for (int i = 0; i < vec->size; i++)
    {
        print("Insira o %dº número: ", i + 1);
        scan("%d", &vec->data[i]);
        if (vec->data[i] < min || vec->data[i] > max)
            i--;
    }
}

void vec_write(vector *vec, int trail)
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

int vec_get_max(vector vec)
{
    int max = vec.data[0];
    for (int i = 1; i < vec.size; i++)
        if (vec.data[i] > max)
            max = vec.data[i];
    return max;
}

int vec_get_min(vector vec)
{
    int min = vec.data[0];
    for (int i = 1; i < vec.size; i++)
        if (vec.data[i] < min)
            min = vec.data[i];
    return min;
}

/*
 *
 * Matrixes
 *
 */

void mat_init(matrix *mat, int cols, int rows)
{
    mat->cols = cols;
    mat->rows = rows;
    mat->data = (int **)malloc(mat->rows * sizeof(int));
    for (int i = 0; i < mat->rows; i++)
        mat->data[i] = (int *)malloc(mat->cols * sizeof(int));
}

void mat_destroy(matrix *mat)
{
    for (int i = 0; i < mat->rows; i++)
        free(mat->data[i]);
    free(mat->data);
}
