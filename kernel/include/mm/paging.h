//file paging.h
//description: create c prototypes for the assembly functions

#ifndef PAGING_H
#define PAGING_H

#define PAGING_GET_DIRECTORY(addr) ((((int)(addr)) & 0xFFC00000) >> 22)
#define PAGING_GET_TABLE(addr) ((((int)(addr)) & 0x3FF000) >> 12)
#define PAGING_GET_OFFSET(addr) (((int)(addr)) & 0xFFF)

#define PAGING_IS_PRESENT(addr) (((int)(addr)) & 1)

static inline long read_esp(void)
{
	long esp;
	__asm__ volatile ("movl %%esp, %0" : "=r"(esp) : );
	return esp;
}

static inline long read_cr0(void)
{
	long cr0;
	__asm__ volatile ("movl %%cr0, %0" : "=r"(cr0) : );
	return cr0;
}

static inline void write_cr0(long cr0)
{
	__asm__ volatile ("movl %0, %%cr0" : : "r"(cr0) );
}

static inline long read_cr2(void)
{
	long cr2;
	__asm__ volatile ("movl %%cr2, %0" : "=r"(cr2) : );
	return cr2;
}

static inline unsigned long *read_cr3(void)
{
	unsigned long *cr3;
	__asm__ volatile ("movl %%cr3, %0" : "=r"(cr3) : );
	return cr3;
}

static inline void write_cr3(void *cr3)
{
	__asm__ volatile ("movl %0, %%cr3" : : "r"(cr3) );
}

static inline void paging_flush_cache()
{
	int cr0 = read_cr0();
	write_cr0(cr0);
}

void *mm_paging_pde_new();
void mm_paging_init();

#endif
