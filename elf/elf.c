#include "elf.h"
#include <stdlib.h>
#include <stdio.h>

static char * readFile(char *filename);
void elf_free(struct exec *e);
void elf_program_headers(struct elf32_header *header);
void elf_section_headers(struct elf32_header *header);

int elf_parse(char *filename, struct exec *e) {
  char *data;
  struct elf32_header *header;

  data = readFile(filename);

  header = (struct elf32_header *)data;

  elf_program_headers(header);
  elf_section_headers(header);

  e->entry = header->entry;

  e->data = data;
  e->free = elf_free;
}

void elf_program_headers(struct elf32_header *header) {
  printf("there are %i program header entries\n", header->phnum);
  if (header->phnum == 0) {
    return;
  }

  struct elf32_program_header *ph = (struct elf32_program_header *)header->ph_offset;
  size_t i;
  for (i = 0; i < header->phnum; i++) {
    printf("loading program header %i\n", i);
  }
}

void elf_section_headers(struct elf32_header *header) {
  printf("there are %i section header entries\n", header->shnum);
}

void elf_free(struct exec *e) {
  printf("cleaning up elf file\n");
  free(e->data);
  free(e);
}

static char * readFile(char *filename) {
  int size = 0;
  FILE *f;
  char *result;

  printf("opening file: %s\n", filename);

  f = fopen(filename, "rb");

  if (f == NULL) {
    printf("Unable to open file\n");
    return NULL;
  }

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);
  result = (char *)malloc(size+1);

  if (size != fread(result, sizeof(char), size, f)) {
    free(result);
    return NULL;
  }
  fclose(f);
  
  printf("Read in %i bytes\n", size);

  return result;
}

int main(int argc, char **args) {
  struct exec *e;
  char *filename; 

  if (argc < 2) {
    printf("Must provide a filename\n");
    return -1;
  }

  filename = args[1];
  e = malloc(sizeof(struct exec));

  elf_parse(filename, e);

  e->entry(0, 0);

  e->free(e);
}
