#ifndef VIRTUAL_MEM_H
#define VIRTUAL_MEM_H

typedef struct page_t {
	unsigned long *address;
	int count;
} page_t;

unsigned long *mm_virtual_page_alloc(page_t*);
void mm_virtual_page_free(page_t*);

static inline unsigned long *mm_convert_virtual_address(int pde, int pte)
{
	return (unsigned long*)((pde << 22) + (pte << 12));
}

static inline int mm_virtual_get_pde(void *address)
{
	return (((unsigned long)address & 0xFFC00000) >> 12);
}

static inline int mm_virtual_get_pte(void *address)
{
	return (((unsigned long)address & 0x3FF000) >> 12);
}

#endif

