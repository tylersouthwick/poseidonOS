#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <mm/paging.h>
#include <mm/virtual_mem.h>
#include <mm/physical_mem.h>

mm_page_header_t *base_page;

/*********************************************************
 * void *mm_virtual_page_alloc()
 *
 * Allocates a new virtual page - being mapped to a physical
 * page.
 * *******************************************************/
void mm_virtual_page_alloc(page_t* page) {
	unsigned long *current_pde, *temp_pte;
	int pde_index, pte_index;
	int count = page->count;

	current_pde = (unsigned long*)((unsigned int)read_cr3() & 0xFFFFF000);

	/*simple case: count==1*/
	if (count == 1)
	{
		for(pde_index=0; pde_index<1024; pde_index++) {
			if (current_pde[pde_index] & 1) {	//is it present?
				temp_pte = (unsigned long*)((long)current_pde[pde_index] & 0xFFFFF000);
				for(pte_index=0; pte_index<1024; pte_index++) {
					if (!(temp_pte[pte_index] & 1)) {
						temp_pte[pte_index] = (unsigned long)mm_physical_page_alloc(MM_TYPE_NORMAL);
						temp_pte[pte_index] |= 3;
						
						page->address = mm_convert_virtual_address(pde_index, pte_index);
						return;
					}
				}
			}
		}
	} else {
		/*this is a little tricky:
		 * we have to find count contigous pages.  Right now, the easiest 
		 * way to do this (also a very very inefficient way) is to scan 
		 * through the page tables looking for a free page, then see if 
		 * there is a free page after that, and after that, until there
		 * is a contigous chunk of virtual pages*/
		unsigned int temp_count = count;
		unsigned int start_index_pte = 0;
		unsigned int start_index_pde = 0;
		unsigned int end_index_pte = 0;
		unsigned int end_index_pde = 0;
		
		for(pde_index=0; pde_index<1024; pde_index++) {
			if (current_pde[pde_index] & 1) {	//is it present?
				temp_pte = (unsigned long*)((long)current_pde[pde_index] & 0xFFFFF000);
				for(pte_index=0; pte_index<1024; pte_index++) {
					if (!(temp_pte[pte_index] & 1)) {

						if (temp_count == count)
						{
							start_index_pde = end_index_pde = pde_index;
							start_index_pte = end_index_pte = pte_index;
							temp_count--;
							continue;
						}

						if ((end_index_pde == pde_index && end_index_pte + 1 == pte_index) || (end_index_pde + 1 == pde_index && !pte_index))
						{
							end_index_pte = pte_index;
							end_index_pde = pde_index;
							temp_count--;

							if (!temp_count)
							{
								if (start_index_pde == end_index_pde)
								{
									int i;
									unsigned long *temp_pte = (unsigned long *)((long)current_pde[start_index_pde] & 0xFFFFF000);
									for(i=start_index_pte; i <= end_index_pte; i++)
									{
										unsigned long addr = (unsigned long)mm_physical_page_alloc(MM_TYPE_NORMAL);

										temp_pte[i] = addr;
										temp_pte[i] |= 3;
									}
									page->address = mm_convert_virtual_address(start_index_pde, start_index_pte);
									return;
								}

								while(1);
							}
						} else {
							temp_count = count;
							start_index_pte = start_index_pde = end_index_pte = end_index_pde = 0;
						}
					}
				}
			}
		}
	}

	kprint("ERROR: mm_virtual_page_alloc() :: reached end of function");
	asm volatile ("cli");
	asm volatile ("hlt");
	while(1);
}

/*********************************************************
 * void *mm_virtual_page_free()
 *
 * frees a mapped virtual page
 * *******************************************************/

void mm_virtual_page_free(page_t *page) {
				/*
	unsigned long *pde,*pte;

	pde = (unsigned long *)read_cr3();

	pte = (unsigned long *)pde[0];
	pte = (unsigned long *)((unsigned int)pte & 0xFFFFF000);
	pte[((int)page->address)/4096] &= 0xFFFFFFFC;
	*/
	kprint("WARNING :: mm_virtual_page_free is not implemented\n");
	return;	
}

