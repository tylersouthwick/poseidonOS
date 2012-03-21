#ifndef VIRTUAL_MEM_H
#define VIRTUAL_MEM_H

typedef struct page_t {
	unsigned long *address;
	int count;
} page_t;

unsigned long *mm_virtual_page_alloc(page_t*);
unsigned long *mm_virtual_mem_new_address_space(void);
void mm_virtual_page_free(page_t*);

static inline unsigned long *mm_convert_virtual_address(int pde, int pte)
{
	return (unsigned long*)((pde << 22) + (pte << 12));
}

static inline int mm_virtual_get_pde(void *address)
{
	return (unsigned long)address >> 22;
}

static inline int mm_virtual_get_pte(void *address)
{
	return (unsigned long) address >> 12 & 0x03FF;
}

#define PAGE_PRESENT 1
#define MM_IS_PRESENT(n) (((int)n) & PAGE_PRESENT)

#define KERNELSPACE_PAGE_START 0
#define KERNELSPACE_PAGE_END 300

#endif

