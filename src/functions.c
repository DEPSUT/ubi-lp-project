#include "functions.h"

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

void scan(const char *string, ...)
{
    int c;

    while (isspace(c = getchar()))
        if (c == '\n')
            lines += 1;

    ungetc(c, stdin);

    va_list args;
    va_start(args, string);
    vscanf(string, args);
    lines += 1;
    va_end(args);
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void print(const char *string, ...)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == '\n')
            lines += 1;
    va_list args;
    va_start(args, string);
    vprintf(string, args);
    va_end(args);
}

void flushBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void waitForEnter()
{
    getchar();
    lines += 1;
}