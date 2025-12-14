/**
 * @file functions.h
 * @brief Biblioteca de Utilitários de @a I/O e Manipulação de @c Strings.
 * Fornece funções @c wrapper para @c scanf() e @c printf() que gerem automaticamente
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
 * @brief Compara duas @c strings.
 * @retval int @c 1 se forem iguais, @c 0 caso contrário.
 */
int stringsAreEqual(char *string1, char *string2);

/**
 * @brief Limpa a saída do terminal (apenas as linhas geradas pelo programa).
 * Utiliza sequências de escape ANSI baseadas na variável global @c lines.
 */
void clearOutput();

/**
 * @brief Calcula o número de dígitos de um inteiro.
 * Útil para calcular o alinhamento (@a padding) em tabelas.
 */
int numOfDig(int num);

/**
 * @brief @a Wrapper seguro para @c scanf().
 * - Consome @c whitespace inicial para contar linhas corretamente.
 * - Incrementa a variável global @c lines.
 * - Limpa o @c buffer após a leitura.
 * @param string @c String de formatação (ex: "%d").
 * @param ... Argumentos a serem passados a @c scanf().
 */
void scan(const char *string, ...);

/**
 * @brief @a Wrapper para @c printf().
 * Conta o número de @c \n na @c string para atualizar o contador global @c lines.
 * @param string String de formatação.
 * @param ... Argumentos a serem passados a @c printf().
 */
void print(const char *string, ...);

/**
 * @brief Pausa a execução até o utilizador pressionar @c ENTER.
 */
void waitForEnter();

#endif
