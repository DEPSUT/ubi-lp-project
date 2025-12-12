#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

extern int lines; // Lines to be deleted from bottom up

int stringsAreEqual(char *string1, char *string2);

void clearOutput();

int numOfDig(int num);

void scan(const char *string, ...);

void print(const char *string, ...);

void flushBuffer();

void waitForEnter();

#endif
