#include <math.h>

#include "lialg.h"
#include "functions.h"

#define DEBUGGING_ENABLED 1

#if DEBUGGING_ENABLED
#include <time.h>
#endif

#define TAM 20
#define MIN -3
#define MAX 18

#define MENU_TITLE "MENU"

// const char menu[2][9][] = ;

#if DEBUGGING_ENABLED
void generateRandomVector(vector *vec)
{
    for (int i = 0; i < vec->size; i++)
        vec->data[i] = rand() % (MAX + abs(MIN) + 1) - abs(MIN);
}
#endif

void showMenu(char *title)
{
    print("\n================%s================\n\n", title);
    print("1 - Máximo\n");
    print("2 - Seno dos elementos\n");
    print("3 - Elementos divisíveis por 3\n");
    print("4 - Matriz com vetor lido e vetor ordernado por ordem crescente\n");
    print("5 - Multiplicar o vetor por 3\n");
    print("6 - Vetor ordernado por ordem crescente\n");
    print("7 - Menu de Ajuda\n\n");
#if DEBUGGING_ENABLED
    print("10 - Gerar novos números para o vetor\n\n");
#endif
    print("0 - Sair\n\n");
    print(":");
}

void helpPage()
{
    int option = 0;
    do
    {
        showMenu("MENU DE AJUDA");
        scan("%d", &option);
        switch (option)
        {
        case 0:
            break;

        default:
            break;
        }
    } while (option != 0);
}

int main(int argc, char **argv)
{
    vector vec;
    int option = -1;

    if (argc == 2 && stringsAreEqual(argv[1], "--help"))
        helpPage();

    vec_init(&vec, TAM);
    print("Insira %d números inteiros entre %d e %d\n", vec.size, MIN, MAX);

#if DEBUGGING_ENABLED
    srand(time(NULL));
    generateRandomVector(&vec);
#else
    vec_read(&vec, MIN, MAX);
#endif

    while (option != 0)
    {
        lines = 0;

#if DEBUGGING_ENABLED
        {
            int max = vec_get_max(vec);
            int trail = numOfDig(vec_get_min(vec));
            if (trail < numOfDig(max))
                trail = numOfDig(max);
            print("Números selecionados:\n");
            for (int i = 0; i < vec.size; i++)
            {
                print("%*d ", trail, vec.data[i]);
                if ((i + 1) % 5 == 0)
                    print("\n");
            }
        }
#endif

        showMenu(MENU_TITLE);

        scan("%d", &option);

        int max = vec_get_max(vec);
        int trail = numOfDig(vec_get_min(vec));
        if (trail < numOfDig(max))
            trail = numOfDig(max);
        switch (option)
        {
        case 1:
            print("O elemento máximo do vetor é %d\n\n", max);
            break;

        case 2:
        {
            print("Seno de cada elemento:\n");
            // Trail of spaces for the result of sine (formats nicely)
            const int sinTrail = 9;
            for (int i = 0; i < vec.size; i++)
            {
                if ((i + 1) % 5 == 0)
                    print("%*d: %*.6f\n", trail, vec.data[i], sinTrail, sin(vec.data[i]));
                else
                    print("%*d: %*.6f, ", trail, vec.data[i], sinTrail, sin(vec.data[i]));
            }
            print("\n");
        }
        break;

        case 3:
        {
            print("Elementos divisíveis por 3:\n");
            int count = 0;
            for (int i = 0; i < vec.size; i++)
                if (vec.data[i] % 3 == 0)
                {
                    count++;
                    if (count > 1)
                        print(", %*d", trail, vec.data[i]);
                    else
                        print("%*d", trail, vec.data[i]);
                }
            print("\n\n");
        }
        break;

        case 4:
        {
            print("Vetor original e vetor ordernado por ordem crescente respetivamente:\n");
            matrix mat;
            mat_init(&mat, vec.size, 2);
            for (int i = 0; i < vec.size; i++)
            {
                mat.data[0][i] = vec.data[i];
                mat.data[1][i] = mat.data[0][i];
            }
            vector tempVec;
            tempVec.data = mat.data[1];
            tempVec.size = mat.cols;
            vec_sort_asc(&tempVec);
            for (int i = 0; i < mat.rows; i++)
            {
                tempVec.data = mat.data[i];
                vec_write(&tempVec, trail);
            }
            mat_destroy(&mat);
            print("\n");
        }
        break;

        case 5:
        {
            trail += 1;
            print("Elementos do vetor multiplicados por 3:\n");
            for (int i = 0; i < vec.size; i++)
            {
                int res = vec.data[i] * 3;
                if ((i + 1) % 5 == 0)
                    print("%*d\n", trail, res);
                else
                    print("%*d, ", trail, res);
            }
            print("\n");
        }
        break;

        case 6:
        {
            vector sortedVec;
            vec_copy_from_to(&vec, &sortedVec);
            vec_sort_asc(&sortedVec);
            print("Vetor ordenado por ordem crescente:\n");
            vec_write(&sortedVec, trail);
            print("\n");
            vec_destroy(&sortedVec);
        }
        break;

        case 7:
            helpPage();
            break;

#if DEBUGGING_ENABLED
        case 10:
            generateRandomVector(&vec);
            break;
#endif

        case 0:
            continue;

        default:
            break;
        }
        print("Pressione ENTER para prosseguir...");
        waitForEnter();
        clearOutput();
    }

    vec_destroy(&vec);
    return 0;
}