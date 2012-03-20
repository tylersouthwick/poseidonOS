#ifndef EXEC_ELF_H
#define EXEC_ELF_H

#define ELFCLASS32 1
#define ELFCLASS64 2

#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define ELF_INVALID_HEADER 1
#define ELF_INVALID_HEADER_MAGIC 2
#define ELF_INVALID_HEADER_32_BITS 3
#define ELF_INVALID_HEADER_ENCODING 4
#define ELF_INVALID_HEADER_VERSION 5

#define PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0x7fffffff

typedef struct {
	char magic[4];
	char ei_class;
	char ei_data;
	char ei_version;
	char ei_padding[9];
} elf_ident_t;

typedef struct {

    unsigned  char    ident[16];
    unsigned  short   type;
    unsigned  short   machine;
    unsigned  int     version;
    unsigned  int     entry;
    unsigned  int     phoff;
    unsigned  int     shoff;
    unsigned  int     flags;
    unsigned  short   ehsize;
    unsigned  short   phentsize;
    unsigned  short   phnum;
    unsigned  short   shentsize;
    unsigned  short   shnum;
    unsigned  short   shstrndx;

} elf_header_t;

typedef struct {

    unsigned  int   type;
    unsigned  int   offset;
    unsigned  int   vaddr;
    unsigned  int   paddr;
    unsigned  int   fileSize;
    unsigned  int   memSize;
    unsigned  int   flags;
    unsigned  int   alignment;

} elf_program_header_t;

#include <exec.h>

int elf_parse(unsigned char *data, int size, exe_format_t *exe);
#endif
