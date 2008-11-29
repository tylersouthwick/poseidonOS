#ifndef STDIO_H
#define STDIO_H

#include "file.h"

//void print(char *string);
void print();
FILE fopen(char* path);
void fclose(FILE file);

#endif

