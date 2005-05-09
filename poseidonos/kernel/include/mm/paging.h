//file paging.h
//description: create c prototypes for the assembly functions

#ifndef PAGING_H
#define PAGING_H


#define PAGING_GET_DIRECTORY(addr) ((((int)(addr)) & 0xFFC00000) >> 22)
#define PAGING_GET_TABLE(addr) ((((int)(addr)) & 0x3FF000) >> 12)
#define PAGING_GET_OFFSET(addr) (((int)(addr)) & 0xFFF)

#define PAGING_IS_PRESENT(addr) (((int)(addr)) & 1)

extern int read_cr0(void);
extern void write_cr0(int);
extern int read_cr2(void);
extern int read_cr3(void);
extern void write_cr3(void *);

void *mm_paging_pde_new(void);

#endif
