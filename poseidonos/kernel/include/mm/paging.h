//file paging.h
//description: create c prototypes for the assembly functions

#ifndef PAGING_H
#define PAGING_H


#define PAGING_GET_DIRECTORY(addr) ((((int)(addr)) & 0xFFC00000) >> 22)
#define PAGING_GET_TABLE(addr) ((((int)(addr)) & 0x3FF000) >> 12)
#define PAGING_GET_OFFSET(addr) (((int)(addr)) & 0xFFF)

#define PAGING_IS_PRESENT(addr) (((int)(addr)) & 1)

static inline int read_cr0(void)
{
	int cr0;
	asm volatile ("movl %%cr0, %0" : "=r"(cr0) : );
	return cr0;
}

static inline void write_cr0(int cr0)
{
	asm volatile ("movl %0, %%cr0" : : "r"(cr0) );
}

static inline int read_cr2(void)
{
	int cr2;
	asm volatile ("movl %%cr2, %0" : "=r"(cr2) : );
	return cr2;
}

static inline int read_cr3(void)
{
	int cr3;
	asm volatile ("movl %%cr3, %0" : "=r"(cr3) : );
	return cr3;
}

static inline void write_cr3(void *cr3)
{
	asm volatile ("movl %0, %%cr3" : : "r"(cr3) );
}

static inline void paging_flush_cache(void)
{
	int cr0 = read_cr0();
	write_cr0(cr0);
}

void *mm_paging_pde_new(void);

#endif
