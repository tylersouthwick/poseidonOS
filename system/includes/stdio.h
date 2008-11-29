#ifndef STDIO_H
#define STDIO_H

#include "file.h"

void print(char* string);
FILE fopen(char* path);
void fclose(FILE file);

#endif

