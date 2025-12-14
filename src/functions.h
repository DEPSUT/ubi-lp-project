/**
 * @file functions.h
 * @brief Biblioteca de Utilitários de _I/O_ e Manipulação de `Strings`.
 * Fornece funções _wrapper_ para `scanf()` e `printf()` que gerem automaticamente
 * a contagem de linhas para permitir a limpeza correta do ecrã.
 * @authors Rafael Reis, Diogo Rodrigues, António Gaspar, Martim Roque
 * @version 1.6
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

/**
 * @brief Contador global de linhas impressas/lidas desde a última limpeza.
 * Usado para calcular quantas linhas o cursor deve subir.
 */
extern int lines;

/**
 * @brief Compara duas `strings`.
 * @retval int `1` se forem iguais, `0` caso contrário.
 */
int stringsAreEqual(char *string1, char *string2);

/**
 * @brief Limpa a saída do terminal (apenas as linhas geradas pelo programa).
 * Utiliza sequências de `escape ANSI` baseadas na variável global `lines`.
 */
void clearOutput();

/**
 * @brief Calcula o número de dígitos de um inteiro.
 * Útil para calcular o alinhamento (_padding_) em tabelas.
 */
int numOfDig(int num);

/**
 * @brief _Wrapper_ seguro para `scanf()`.
 * - Consome `whitespace` inicial para contar linhas corretamente.
 * - Incrementa a variável global `lines`.
 * - Limpa o `buffer` após a leitura.
 * @param string `String` de formatação (ex: "%d").
 * @param ... Argumentos a serem passados a `scanf()`.
 */
void scan(const char *string, ...);

/**
 * @brief _Wrapper_ para `printf()`.
 * Conta o número de `\n` na `string` para atualizar o contador global `lines`.
 * @param string `String` de formatação.
 * @param ... Argumentos a serem passados a `printf()`.
 */
void print(const char *string, ...);

/**
 * @brief Pausa a execução até o utilizador pressionar `ENTER`.
 */
void waitForEnter();

#endif
