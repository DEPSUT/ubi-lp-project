#include "lialg.h"
#include "functions.h"
#include "menu_functions.h"
#include "config.h"

#if DEBUGGING_ENABLED
#include <time.h>
#endif

int main(int argc, char **argv)
{
    vector vec;
    int page = 0;
    int option = -1;
    lines--;

    if (argc == 2 && stringsAreEqual(argv[1], "--help"))
        menu_help_page(NULL);

    vec_init(&vec, TAM);
    print("Insira %d números inteiros entre %d e %d\n", vec.size, MIN, MAX);

#if DEBUGGING_ENABLED
    // Inicializa o gerador de números aleatórios com o tempo atual
    // para que seja um valor que mude constantemente
    srand(time(NULL));
    generateRandomVector(&vec);
#else
    vec_read(&vec, MIN, MAX);
#endif

    while (option != 0)
    {
        clearOutput();
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

        int start = menu_show(page, &option);
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
        case 0:
            continue;
#if DEBUGGING_ENABLED
        case 10:
            generateRandomVector(&vec);
            continue;
#endif
        default:
            if(option > ITEMS_PER_PAGE)
                continue;
            option += start;
        }
        if (option <= TOTAL_ITEMS && option > 0)
        {
            menu[option - 1].action(&vec);
            print("Pressione ENTER para prosseguir...");
            waitForEnter();
        }
    }

    vec_destroy(&vec);
    return 0;
}