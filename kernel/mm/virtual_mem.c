#include <ktypes.h>
#include <kdebug.h>

#include <mm/paging.h>
#include <mm/virtual_mem.h>
#include <mm/physical_pages.h>
#include <screen.h>

mm_page_header_t *base_page;

/*********************************************************
 * void *mm_virtual_page_alloc(page_t *page)
 *
 * Allocates a new virtual page - being mapped to a physical
 * page.  page->count must be specified (>0) and tells how
 * many contigous pages to allocate.  If it is less than zero,
 * then it is assumed to be one and changed accordingly.
 *
 * Returns: positive integer (address) on success
 * 					zero (0) on failure
 * *******************************************************/
unsigned long *mm_virtual_page_alloc(page_t* page) {
	unsigned long *temp_pte;
	int pde_index, pte_index;
	int count = page->count;

	const unsigned long *current_pde = (unsigned long*)((unsigned int)read_cr3() & 0xFFFFF000);

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
						return page->address;
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
									return page->address;
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

	return (unsigned long*)0;
}

/*********************************************************
 * void *mm_virtual_page_free()
 *
 * frees a mapped virtual page
 * *******************************************************/
void mm_virtual_page_free(page_t *page) {
	int i;
	unsigned long *page_directory = (unsigned long *)read_cr3();
	unsigned int pde_index = mm_virtual_get_pde(page->address);
	unsigned int pte_index = mm_virtual_get_pte(page->address);
	unsigned long *current_pde = (unsigned long *)(page_directory[pde_index] & 0xFFFFF000);

	DEBUG_MSG(("address first: 0x%x", page->address));

	for (i=pte_index; i<(pte_index + page->count); i++) {
		//unsigned long address = current_pde[i];
		//DEBUG_MSG(("address: 0x%x", address));
		current_pde[i] = 0;
	}
}

void mm_virtual_bind_address(unsigned long *cr3, unsigned long *physical_address, unsigned long *virtual_address, unsigned int flags) {
	TRACE_MSG(("binding 0x%x -> 0x%x in page directory @ 0x%x", virtual_address, physical_address, cr3));

	const unsigned long *current_pde = (unsigned long*)((unsigned int)cr3 & 0xFFFFF000);

	const unsigned long pdindex = mm_virtual_get_pde(virtual_address);
	const unsigned long ptindex = mm_virtual_get_pte(virtual_address);

	TRACE_MSG(("adding page table @ page_dir_index=%i page_table_index=%i", pdindex, ptindex));

	unsigned long pte = cr3[pdindex];
	unsigned long *pt = (unsigned long *)(pte & 0xFFFFF000);

	if (!MM_IS_PRESENT(pte)) {
		TRACE_MSG(("page table is non-existant"));
		//add the pde
		TRACE_MSG(("Adding pde %i", pdindex));
		pt = mm_physical_page_alloc(MM_TYPE_NORMAL);
		TRACE_MSG(("setting pde %i", pdindex));
		cr3[pdindex] = ((unsigned long)pt) | 3;
		int new_pdindex = mm_virtual_get_pde(pt);
		if (new_pdindex == pdindex) {
			ERROR_MSG(("What to do?"));
			while(1);
		}
		mm_virtual_bind_address(cr3, pt, pt, flags);
		memset(pt, 0, 4096);
		TRACE_MSG(("Added pde %i", pdindex));
	}

	pt[ptindex] = ((unsigned long) physical_address) | (flags & 0xFFF) | PAGE_PRESENT | 3;
	TRACE_MSG(("bound 0x%x -> 0x%x", virtual_address, physical_address));
}

/********************************************************
 * unsigned long *virtual_mem_new_address_space()
 * *****************************************************/
unsigned long *mm_virtual_mem_new_address_space() {
	//unsigned int pte;
	//unsigned long *current_pte;

	DEBUG_MSG(("creating new address space"));
	__asm__ volatile ("cli");


	/*allocate space for the page directory*/
	const unsigned long *current_cr3 = read_cr3();

	unsigned long *new_cr3 = mm_physical_page_alloc(MM_TYPE_NORMAL);
	DEBUG_MSG(("new_cr3: 0x%x", new_cr3));
	mm_virtual_bind_address(current_cr3, new_cr3, new_cr3, 0);
	memset(new_cr3, 0, 4096);
	write_cr3(read_cr3());

	for (unsigned int pde = KERNELSPACE_PAGE_START; pde < KERNELSPACE_PAGE_END; pde++) {
		if (!MM_IS_PRESENT(current_cr3[pde])) continue;
		TRACE_MSG(("current_cr3[pde]: 0x%x", current_cr3[pde]));

		TRACE_MSG(("copying cr3 entry..."));
		new_cr3[pde] = current_cr3[pde];
		/*
		for (pte=0; pte < 1024; pte++)
		{
			if (MM_IS_PRESENT(current_pte[pte])) break;
			current_
		}
		*/
	}
	DEBUG_MSG(("created new address space!"));

	__asm__ volatile ("sti");
	return new_cr3;
}

int mm_alloc_virtual_address_range(unsigned long *cr3, unsigned long *start, size_t size) {
	const int pageCount = size / 4096 + 1;
	TRACE_MSG(("Allocate virtual address range @0x%x of %i pages", start, pageCount));
	unsigned long current_page = start;
	const unsigned long *current_cr3 = read_cr3();
	for (int i = 0; i < pageCount; i++) {
		TRACE_MSG(("Binding address %i @0x%x", i, current_page));
		unsigned long *page = mm_physical_page_alloc(MM_TYPE_NORMAL);
		mm_virtual_bind_address(cr3, page, current_page, 0);
		mm_virtual_bind_address(current_cr3, page, current_page, 0);
		current_page += 4096;
	}
	return 0;
}
