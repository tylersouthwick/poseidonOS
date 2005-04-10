#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <paging.h>
#include <virtual_mem.h>

unsigned long current_pte;
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
					temp_pte[pte_index] = (unsigned long)mm_physical_page_alloc();
					temp_pte[pte_index] |= 3;
					return (void *)((pde_index << 20) + (pte_index << 12));
				}
			}
		}
	}

	kprint("ERROR: mm_virtual_page_alloc()");
	asm("cli");
	asm("hlt");
	while(1);
}

/*************************************************
 * void *mm_virtual_page_alloc_user()
 *
 * Very similar to the above function, but 
 * garuntees that the page is in userspace
 * ***********************************************/
void *mm_virtual_page_alloc_user() {
	unsigned long *current_pde, *temp_pte;
	int pde_index, pte_index;
	
	current_pde = (unsigned long*)((unsigned int)read_cr3() & 0xFFFFF000);

	for(pde_index=512; pde_index<1024; pde_index++) {
					/*
						kprint("current_pde[");
						put_int(pde_index, 10);
						kprint("] : ");
						put_int(current_pde[pde_index], 2);
						kprint("\n");
						*/
		if ((current_pde[pde_index] & 1)) {	//is it present?
			temp_pte = (unsigned long*)((long)current_pde[pde_index] & 0xFFFFF000);
			for(pte_index=0; pte_index<1024; pte_index++) {
				if (!(temp_pte[pte_index] & 1)) {
					temp_pte[pte_index] = (unsigned long)mm_physical_page_alloc();
					temp_pte[pte_index] |= 3;
					return (void *)((pde_index << 20) + (pte_index << 12));
				}
			}
		}
	}

	kprint("ERROR: mm_virtual_page_alloc_user()");
	asm("cli");
	asm("hlt");
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

