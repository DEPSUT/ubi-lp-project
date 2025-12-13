#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H

#include <math.h>

#include "lialg.h"
#include "functions.h"
#include "config.h"

typedef struct menuItem
{
    const char *title;
    const char *help;
    // Ponteiro para função que retorna void e recebe void*
    // Dinamiza a organização do menu
    void (*action)(void *vec);
} menuItem;

extern const menuItem menu[];

extern const int TOTAL_ITEMS;

extern const int TOTAL_PAGES;

#if DEBUGGING_ENABLED
void generateRandomVector(vector *vec);
#endif

void menu_max(void *_vec);

void menu_sin(void *_vec);

void menu_div_3(void *_vec);

void menu_sorted_matrix(void *_vec);

void menu_mult_3(void *_vec);

void menu_sorted_vector(void *_vec);

void menu_sum_second_vector(void *_vec);

void menu_help_page(void *_vec);

int menu_show(int page, int *option);

#endif