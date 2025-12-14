/**
 * @file menu_functions.c
 * @brief Implementação da lógica de negócio das opções do menu.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.0
 */

#include "menu_functions.h"

/**
 * @brief Tabela de Despacho (_Dispatch Table_) do menu.
 * Substitui a necessidade de grandes estruturas `switch`.
 * Cada linha contém metadados e um ponteiro para a função a executar.
 */
const menuItem menu[] = {
    {"Máximo", "Mostra o maior valor inserido no vetor.", menu_max, 1},
    {"Seno", "Calcula e apresenta o valor do seno de cada elemento do vetor.", menu_sin, 1},
    {"Divisíveis por 3", "Mostra todos os elementos do vetor que são divisíveis por 3.", menu_div_3, 1},
    {"Matriz ordernada", "Mostra uma matriz em que a primeira linha mostra o vetor original e a segunda linha mostra o vetor ordernado por ordem crescente.", menu_sorted_matrix, 1},
    {"Multiplicar por 3", "Mostra todos os elementos do vetor multiplicados por 3.", menu_mult_3, 1},
    {"Vetor ordernado", "Mostra o vetor ordenado por ordem crescente.", menu_sorted_vector, 1},
    {"Menu de Ajuda", "Mostra este menu de ajuda.", menu_help_page, 0},
    {"Soma com segundo vetor", "Pede a leitura de um novo vetor e calcula a soma do primeiro vetor com o dobro do segundo vetor.", menu_sum_second_vector, 1},
    {"Decomposição em números primos", "Mostra a decomposição em números primos de cada elemento do vetor.", menu_prime_decomposition, 1},
    {"Matriz 20x20", "Leitura de um novo vetor, cálculo e apresentação da matriz 20x20 resultante do produto do vetor inicial com o novo vetor lido.", menu_matrix_20x20, 1},
    {"Determinante", "Calcula e apresenta a determinante da matriz criada na opção anterior.", menu_matrix_determinant, 0},
};


const int TOTAL_ITEMS = sizeof(menu) / sizeof(menu[0]);                         ///< Total de itens em `menu[]`
const int TOTAL_PAGES = (TOTAL_ITEMS + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;    ///< Número total de páginas do menu tendo em conta `ITEMS_PER_PAGE`

/**
 * @brief Matriz persistente gerada pela opção 10.
 * Declarada como `static` para restringir o `scope` a este ficheiro.
 */
static matrix stored_matrix;       ///< Guarda o valor da matriz para ser utilizada noutra opção do menu
static int matrix_initialized = 0; ///< Permite saber se a matriz já foi criada

#if DEBUGGING_ENABLED
void generateRandomVector(vector *vec)
{
    for (int i = 0; i < vec->size; i++)
        vec->data[i] = rand() % (MAX + abs(MIN) + 1) - abs(MIN);
}
#endif

int getTrail(vector *vec)
{
    int max = vec_get_max(vec);
    int trail = numOfDig(vec_get_min(vec));
    if (trail < numOfDig(max))
        trail = numOfDig(max);
    return trail;
}

// Funções para os items do menu
void menu_max(void *_vec)
{
    vector *vec = (vector *)_vec;
    print("O elemento máximo do vetor é %d\n\n", vec_get_max(vec));
}

void menu_sin(void *_vec)
{
    vector *vec = (vector *)_vec;
    print("Seno de cada elemento:\n");
    const int trail = getTrail(vec);
    const int sinTrail = 9;
    for (int i = 0; i < vec->size; i++)
    {
        if ((i + 1) % 5 == 0)
            print("%*d: %*.6f\n", trail, vec->data[i], sinTrail, sin(vec->data[i]));
        else
            print("%*d: %*.6f, ", trail, vec->data[i], sinTrail, sin(vec->data[i]));
    }
    print("\n");
}

void menu_div_3(void *_vec)
{
    vector *vec = (vector *)_vec;

    print("Elementos divisíveis por 3:\n");
    const int trail = getTrail(vec);
    int count = 0;
    for (int i = 0; i < vec->size; i++)
        if (vec->data[i] % 3 == 0)
        {
            count++;
            if (count > 1)
                print(", %*d", trail, vec->data[i]);
            else
                print("%*d", trail, vec->data[i]);
        }
    print("\n\n");
}

void menu_sorted_matrix(void *_vec)
{
    vector *vec = (vector *)_vec;

    print("Vetor original e vetor ordernado por ordem crescente respetivamente:\n");

    matrix mat;
    mat_init(&mat, vec->size, 2);

    const int trail = getTrail(vec);

    for (int i = 0; i < vec->size; i++)
    {
        mat.data[0][i] = vec->data[i];
        mat.data[1][i] = mat.data[0][i];
    }

    vector tempVec;
    tempVec.data = mat.data[1];
    tempVec.size = mat.cols;
    vec_sort_asc(&tempVec);
    for (int i = 0; i < mat.rows; i++)
        tempVec.data = mat.data[i];

    mat_write(&mat, trail);
    mat_destroy(&mat);
    print("\n");
}

void menu_mult_3(void *_vec)
{
    vector *vec = (vector *)_vec;
    print("Elementos do vetor multiplicados por 3:\n");
    const int trail = getTrail(vec) + 1;
    for (int i = 0; i < vec->size; i++)
    {
        int res = vec->data[i] * 3;
        if ((i + 1) % 5 == 0)
            print("%*d\n", trail, res);
        else
            print("%*d, ", trail, res);
    }
    print("\n");
}

void menu_sorted_vector(void *_vec)
{
    vector *vec = (vector *)_vec;
    const int trail = getTrail(vec);
    vector sortedVec;
    vec_copy_from_to(vec, &sortedVec);
    vec_sort_asc(&sortedVec);
    print("Vetor ordenado por ordem crescente:\n");
    vec_write(&sortedVec, trail);
    print("\n");
    vec_destroy(&sortedVec);
}

void menu_help_page(void *_)
{
    int option = -1;
    int page = 0;
    while (option != 0)
    {
        clearOutput();
        lines = 0;
        int start = page * ITEMS_PER_PAGE;
        int end = start + ITEMS_PER_PAGE;
        if (end > TOTAL_ITEMS)
            end = TOTAL_ITEMS;

        print("\n================ MENU DE AJUDA (Pág %d/%d) ================\n\n", page + 1, TOTAL_PAGES);
        int k = 1;
        for (int i = start; i < end; i++, k++)
        {
            print("%d - %s\n", k, menu[i].title);
            print("\t-> %s\n", menu[i].help);
        }

        if (TOTAL_PAGES > 1)
            print("\n");
        if (TOTAL_PAGES > 1 && page > 0)
            print("8 - Página anterior\n");
        if (TOTAL_PAGES - 1 > page)
            print("9 - Página seguinte\n");

        print("\n0 - Voltar\n\n");
        print(":");

        scan("%d", &option);
        switch (option)
        {
        case 8:
            if (page > 0)
                page--;
            continue;
        case 9:
            if (page < TOTAL_PAGES - 1)
                page++;
            continue;

        default:
            break;
        }
    }
}

void menu_sum_second_vector(void *_vec)
{
    vector *vec = (vector *)_vec;
    const int trail = getTrail(vec);
    vector vec2;
    vec_init(&vec2, vec->size);
#if DEBUGGING_ENABLED
    generateRandomVector(&vec2);
#else
    print("Insira valores entre %d e %d para o segundo vetor\n", MIN, MAX);
    vec_read(&vec2, MIN, MAX);
#endif
    vector vec3;
    vec_init(&vec3, vec->size);
    for (int i = 0; i < vec3.size; i++)
        vec3.data[i] = vec->data[i] + (vec2.data[i] * 2);
    print("Segundo vetor lido e resultado da soma do primeiro vetor com o dobro do segundo respetivamente:\n");
    vec_write(&vec2, trail);
    vec_write(&vec3, trail);
    print("\n");
    vec_destroy(&vec2);
    vec_destroy(&vec3);
}

void print_prime_demposition(int num)
{
    switch (num)
    {
    case 0:
    case 1:
    case -1:
        print("%d", num);
        return;
    }

    // Verifica se é o primeiro número a ser
    // escrito para a formatação ser consistente
    int isFirst = 1;
    if (num < 0)
    {
        print("-1");
        num = -num;
        isFirst = 0;
    }

    int k = 2;
    while (num > 1)
    {
        if (num % k == 0)
        {
            if (!isFirst)
                print(" x ");
            print("%d", k);
            num /= k;
            isFirst = 0;
        }
        else
            k++;
    }
}

void menu_prime_decomposition(void *_vec)
{
    vector *vec = (vector *)_vec;
    print("Decomposição dos elementos do vetor em números primos:\n");
    const int trail = getTrail(vec);
    for (int i = 0; i < vec->size; i++)
    {
        print("%*d: ", trail, vec->data[i]);
        print_prime_demposition(vec->data[i]);
        print("\n");
    }
    print("\n");
}

/**
 * @brief Gera uma matriz a partir do produto externo de dois vetores.
 * A matriz resultante é guardada na variável estática `stored_matrix`
 * para poder ser usada posteriormente pela função do determinante.
 * @param _vec Ponteiro `void` para o vetor principal (_cast_ para `vector*` internamente).
 */
void menu_matrix_20x20(void *_vec)
{
    vector *vec = (vector *)_vec;
    const int trail = getTrail(vec);
    vector vec2;
    vec_init(&vec2, vec->size);
#if DEBUGGING_ENABLED
    generateRandomVector(&vec2);
#else
    print("Insira valores entre %d e %d para o segundo vetor\n", MIN, MAX);
    vec_read(&vec2, MIN, MAX);
#endif
    if (matrix_initialized)
        mat_destroy(&stored_matrix);
    vec_mult(&stored_matrix, vec, &vec2);
    matrix_initialized = 1;

    print("Segundo vetor lido:\n");
    vec_write(&vec2, trail);
    vec_destroy(&vec2);

    print("\nMatriz do produto dos dois vetores:\n");
    mat_write(&stored_matrix, trail + 1);
    print("\n");
}

/**
 * @brief _Wrapper_ para calcular o determinante.
 * Verifica se a matriz foi inicializada antes de chamar a função matemática pesada.
 */
void menu_matrix_determinant(void *_)
{
    if (!matrix_initialized)
    {
        print("Para usar esta opção tem primeiro que usar a opção anterior para obter a matriz.\n");
        return;
    }

    print("Determinante da matriz 20x20: %g\n\n", mat_get_determinant(&stored_matrix));
}

void menu_destroy()
{
    if (matrix_initialized)
        mat_destroy(&stored_matrix);
}

int menu_show(int page, int *option)
{
    int start = page * ITEMS_PER_PAGE;
    int end = start + ITEMS_PER_PAGE;
    if (end > TOTAL_ITEMS)
        end = TOTAL_ITEMS;

    print("\n================ MENU (Pág %d/%d) ================\n\n", page + 1, TOTAL_PAGES);
    int k = 1;
    for (int i = start; i < end; i++, k++)
        print("%d - %s\n", k, menu[i].title);

    if (TOTAL_PAGES > 1)
        print("\n");
    if (TOTAL_PAGES > 1 && page > 0)
        print("8 - Página anterior\n");
    if (TOTAL_PAGES - 1 > page)
        print("9 - Página seguinte\n");

#if DEBUGGING_ENABLED
    print("\n10 - Gerar novos números para o vetor\n");
#endif

    print("\n0 - Sair\n\n");
    print(":");

    scan("%d", option);
    return start;
}