#ifndef VIRTUAL_MEM_H
#define VIRTUAL_MEM_H

typedef struct page_t {
	unsigned long *address;
	int count;
} page_t;

unsigned long *mm_virtual_page_alloc(page_t*);
int mm_virtual_page_free(page_t*);

static inline unsigned long *mm_convert_virtual_address(int pde, int pte)
{
	return (unsigned long*)((pde << 22) + (pte << 12));
}

#endif

