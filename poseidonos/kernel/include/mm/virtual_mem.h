#ifndef VIRTUAL_MEM_H
#define VIRTUAL_MEM_H

void *mm_virtual_page_alloc(void);
void *mm_virtual_page_alloc_multiple(int);
void mm_virtual_page_free(void *);

#endif

