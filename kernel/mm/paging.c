#include <ktypes.h>
#include <kdebug.h>

#include <mm/physical_pages.h>
#include <mm/paging.h>

extern mm_physical_page_zones memory_zones;

void mm_paging_init() {
	unsigned long *page_directory;
	unsigned long *page_directory_table;
	unsigned long *page_table;
	unsigned int i;
	unsigned int address;

	DEBUG(("Initializing Virtual Paging"));

	/*get pages*/
	page_directory = (unsigned long*)mm_physical_page_alloc(MM_TYPE_NORMAL);
	page_directory_table = (unsigned long*)mm_physical_page_alloc(MM_TYPE_NORMAL);
	page_table = (unsigned long*)mm_physical_page_alloc(MM_TYPE_NORMAL);

	/*setup page table*/
	address = 0;
	for(i=0; i<1024; i++)
	{
		page_table[i] = address | 3 | 4;
		address += 4096;
	}

	/*insert pte entry*/
	page_directory[0] = ((int)page_table) | 3;

	for (i=1; i < 1024; i++)
		page_directory[i] = 0 | 2 | 4;

	/*map in page_table and page_directory*/
	for(i=0; i<1024; i++)
		page_directory_table[i] = 0 | 2 | 4;

	/*add pages to the page table*/
	page_directory_table[PAGING_GET_TABLE(page_directory)] = (long)page_directory;
	page_directory_table[PAGING_GET_TABLE(page_directory)] |= 3 | 4;

	page_directory_table[PAGING_GET_TABLE(page_directory_table)] = (long)page_directory_table;
	page_directory_table[PAGING_GET_TABLE(page_directory_table)] |= 3 | 4;

	page_directory_table[PAGING_GET_TABLE(page_table)] = (long)page_table;
	page_directory_table[PAGING_GET_TABLE(page_table)] |= 3 | 4;

	page_directory[PAGING_GET_DIRECTORY(page_directory)] = (long)page_directory_table;
	page_directory[PAGING_GET_DIRECTORY(page_directory)] |= 3 | 4;

	write_cr3(page_directory);
	write_cr0(read_cr0() | 0x80000000);

	DEBUG(("Initialized Virtual Paging"));
}

/***************************************************************
 * void *mm_paging_pde_new()
 *
 * sets up a valid pde table, with one pte.  The pde is 
 * self-mapped to it's physical address in the pde
 * ************************************************************/
void *mm_paging_pde_new() {
	unsigned long *temp_pde;
	int i;

	//allocate a new physical page that the pde will be located at
	temp_pde = (unsigned long*)mm_physical_page_alloc(MM_TYPE_NORMAL);

	//mark every pde entry as not-present
	for(i=0; i<1024; i++)
		temp_pde[i] = 0 | 2;

	return temp_pde;
}

/***************************************************************
 * void *mm_paging_pde_insert()
 *
 * inserts a pte in the current pde at the first
 * 'not present' entry
 * ************************************************************/
/*
void *mm_paging_pde_insert() {
	unsigned long *current_pde, *temp_pte;
	int i;

	current_pde = (unsigned long*)read_cr3();
	temp_pte = (unsigned long*) mm_physical_page_alloc(MM_TYPE_NORMAL);

	//search through the pde to find a 'not present' entry
	//set that entry as 'present' and return that address
	for (i=0; i<1024; i++) {
		if (!(current_pde[i] & 1)) { //is it 'not present'?
			//yes
			current_pde[i] = (unsigned long)temp_pte;
			current_pde[i] |= 3;
			
			//flush processor cache
			
			return (void *)(i << 12);
		}
	}
	
	KLOG_DEBUG("ERROR: Unable to insert a page table into the current page directory");
	while(1);
}
*/

