#ifndef VIRTUAL_MEM_H
#define VIRTUAL_MEM_H

void *mm_virtual_page_alloc();
void mm_virtual_page_free(void *v_addr);

#endif

