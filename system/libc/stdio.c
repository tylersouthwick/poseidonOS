#include <stdio.h>

void print() {
  asm ("int $0x45");
}

FILE fopen(char* path) {
  return 0;
}

void fclose(FILE file) {
}
