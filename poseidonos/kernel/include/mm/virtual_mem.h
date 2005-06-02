#ifndef VIRTUAL_MEM_H
#define VIRTUAL_MEM_H

void *mm_virtual_page_alloc(int);
void mm_virtual_page_free(void *);

static inline unsigned long *mm_convert_virtual_address(int pde, int pte)
{
	return (unsigned long*)((pde << 22) + (pte << 12));
}

#endif

