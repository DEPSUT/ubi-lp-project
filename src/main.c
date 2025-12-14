/**
 * @file main.c
 * @brief Ponto de entrada da aplicação.
 * Responsável pela inicialização das estruturas de dados principais,
 * gestão do ciclo de vida do programa (@a Setup -> @a Loop -> @a Teardown) e
 * orquestração da navegação entre páginas do menu.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.9
 */

#include "lialg.h"
#include "functions.h"
#include "menu_functions.h"
#include "config.h"

#if DEBUGGING_ENABLED
#include <time.h>
#endif

/**
 * @brief Função principal.
 * * Fluxo de execução:
 * 1. Inicialização do vetor (aleatória ou manual).
 * 2. Ciclo principal (@a loop) de interação.
 * 3. Renderização do menu e paginação.
 * 4. Execução da ação escolhida via tabela de despacho.
 * 5. Libertação de memória.
 * * @param argc Número de argumentos da linha de comandos.
 * @param argv @c array de @c strings com os argumentos.
 * @retval int @c 0 em caso de sucesso.
 */
int main(int argc, char **argv)
{
    /* --- SETUP --- */
    vector vec;
    int page = 0;
    int option = -1;

    // Verifica argumento --help
    if (argc == 2 && stringsAreEqual(argv[1], "--help"))
        menu_help_page(NULL);

    vec_init(&vec, TAM);

#if DEBUGGING_ENABLED
    // Inicializa o gerador de números aleatórios com o tempo atual
    // para que seja um valor que mude constantemente
    srand(time(NULL));
    generateRandomVector(&vec);
#else
    print("Insira %d números inteiros entre %d e %d\n", vec.size, MIN, MAX);
    vec_read(&vec, MIN, MAX);
#endif

    /* --- LOOP --- */
    while (option != 0)
    {
        clearOutput();
        lines = 0;

#if DEBUGGING_ENABLED
        {
            int trail = getTrail(&vec);
            print("Números selecionados:\n");
            for (int i = 0; i < vec.size; i++)
            {
                print("%*d ", trail, vec.data[i]);
                if ((i + 1) % 5 == 0)
                    print("\n");
            }
        }
#else
        {
            int trail = getTrail(&vec);
            print("Vetor inserido:\n");
            vec_write(&vec, trail);
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
            if (option > ITEMS_PER_PAGE)
                continue;
            option += start;
        }
        if (option <= TOTAL_ITEMS && option > 0)
        {
            option--;
            if (menu[option].useVector)
                menu[option].action(&vec);
            else
                menu[option].action(NULL);
            option++;
            print("Pressione ENTER para prosseguir...");
            waitForEnter();
        }
    }

    /* --- TEARDOWN --- */
    menu_destroy();
    vec_destroy(&vec);
    return 0;
}