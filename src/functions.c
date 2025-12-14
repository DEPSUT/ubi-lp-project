/**
 * @file functions.c
 * @brief Implementação das funções auxiliares de sistema e _I/O_.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.6
 */

#include "functions.h"

/**
 * @brief Variável global para rastrear o cursor vertical.
 * Incrementada sempre que um `\n` é detetado na entrada ou saída.
 */
int lines = 0;

int stringsAreEqual(char *string1, char *string2)
{
    for (int i = 0; string1[i] != '\0' || string2[i] != '\0'; i++)
        if (string1[i] != string2[i])
            return 0;
    return 1;
}

void clearOutput()
{
    printf("\e[%dF\e[0J", lines);
}

int numOfDig(int num)
{
    int count = 1;

    if (num < 0)
        count++;

    while (num /= 10)
        count++;

    return count;
}

/**
 * @brief Implementação segura de leitura de _inputs_.
 * * Resolve problemas de _buffer_ do `scanf()` original e conta as linhas
 * para permitir a limpeza correta do ecrã posteriormente.
 * * Utiliza `va_list` para passar os argumentos para `vscanf()`.
 * @param string Formato (ex: "%d").
 * @param ... Argumentos variáveis (ponteiros para as variáveis).
 */
void scan(const char *string, ...)
{
    int c;

    // Consome whitespace inicial (espaços ou enters que ficaram no buffer)
    // Se encontrar um enter, incrementa o contador de linhas
    while (isspace(c = getchar()))
        if (c == '\n')
            lines += 1;

    ungetc(c, stdin); // Devolve o caracter útil ao stream

    va_list args;
    va_start(args, string);
    vscanf(string, args);
    lines += 1;
    va_end(args);

    // Limpeza final do buffer (flush) até ao fim da linha
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief Implementação de _wrapper_ para `printf()`.
 * Analisa a `string` antes de imprimir para contar quantos `\n` existem
 * e atualizar a variável global `lines`.
 * @param string Texto a imprimir.
 * @param ... Argumentos variáveis.
 */
void print(const char *string, ...)
{
    // Pré-análise para contagem de quebras de linha
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == '\n')
            lines += 1;
    va_list args;
    va_start(args, string);
    vprintf(string, args);
    va_end(args);
}

void waitForEnter()
{
    getchar();
    lines += 1;
}