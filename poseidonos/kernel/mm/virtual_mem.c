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
void *mm_virtual_page_alloc() {
	unsigned long *current_pde, *temp_pte;
	int pde_index, pte_index;

	current_pde = (unsigned long*)((unsigned int)read_cr3() & 0xFFFFF000);

	for(pde_index=0; pde_index<1024; pde_index++) {
		if (current_pde[pde_index] & 1) {	//is it present?
			temp_pte = (unsigned long*)((long)current_pde[pde_index] & 0xFFFFF000);
			for(pte_index=0; pte_index<1024; pte_index++) {
				if (!(temp_pte[pte_index] & 1)) {
					temp_pte[pte_index] = (unsigned long)mm_physical_page_alloc(MM_TYPE_NORMAL);
					temp_pte[pte_index] |= 3;
					return (void *)((pde_index << 22) + (pte_index << 12));
				}
			}
		}
	}

	kprint("ERROR: mm_virtual_page_alloc()");
	asm volatile ("cli");
	asm volatile ("hlt");
	while(1);
}

void mm_virtual_page_free(void *v_addr) {
	unsigned long *pde,*pte;

	pde = (unsigned long *)read_cr3();

	pte = (unsigned long *)pde[0];
	pte = (unsigned long *)((unsigned int)pte & 0xFFFFF000);
	pte[((int)v_addr)/4096] &= 0xFFFFFFFC;
	return;	
}

