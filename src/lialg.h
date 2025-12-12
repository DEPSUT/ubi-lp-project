#ifndef LIALG_H
#define LIALG_H

#include <stdlib.h>

#include "functions.h"

typedef struct vector
{
    int *data;
    int size;
} vector;

typedef struct matrix
{
    int **data;
    int rows;
    int cols;
} matrix;

/* Vectors */
void vec_init(vector *vec, int size);

void vec_copy_from_to(vector *from, vector *to);

void vec_read(vector *vec, int min, int max);

void vec_write(vector *vec, int trail);

void vec_sort_asc(vector *vec);

void vec_destroy(vector *vec);

int vec_get_max(vector vec);

int vec_get_min(vector vec);

/* Matrixes */
void mat_init(matrix *vec, int cols, int rows);

void mat_destroy(matrix *mat);

#endif
