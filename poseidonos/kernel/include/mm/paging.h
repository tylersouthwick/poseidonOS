//file paging.h
//description: create c prototypes for the assembly functions

#ifndef PAGING_H
#define PAGING_H

extern int read_cr0();
extern void write_cr0(int value);
extern int read_cr2();
extern int read_cr3();
extern void write_cr3(void *value);

void *mm_paging_pde_new();

#endif
