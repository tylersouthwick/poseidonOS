#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <physical_mem.h>
#include <paging.h>

void mm_paging_init() {
	//unsigned long address=0;
	unsigned long *temp_pde, *temp_pte;
	//int i,h;
	int buffer,count;
	int superpage_index, subpage_index;

	temp_pde = mm_paging_pde_new();

	//insert pte entry
	temp_pte = (unsigned long*)mm_physical_page_alloc();
	temp_pde[0] = ((int)temp_pte) | 3;
	
	//mark pages as used according to mm_physical_bitmap
	//this will only search through the first 4MB of memory to map into a virutal address
	//there theoretically SOULDN'T be any more (so far its just the kernel running!)

	//there are 0x400 pages in 4MB
	//making 0x80 superpages
	count = 0;

	for (superpage_index=0; superpage_index<0x80; superpage_index++) {
		if (mm_physical_bitmap[superpage_index] != 0) {//at least one free page
			for (subpage_index=0; subpage_index<8; subpage_index++) {
				buffer = ((superpage_index << 3) & 0xFFFFFFF8) + subpage_index;
				if ((mm_physical_bitmap[superpage_index] >> subpage_index) & 0x1) {
					//physical page exists
					temp_pte[buffer] = MM_PHYSICAL_BITMAP_ADR(superpage_index, subpage_index);
					temp_pte[buffer] |= 3;
					count++;
				} else 
					//put an empty address marked as 'not present'					
					temp_pte[buffer] = 2;
			}
		}
	}

#ifdef DEBUG_MM
	//start paging!
	kprint("kernel end: ");
	put_int(end_of_kernel,16);
	kprint("\nenabling paging...");
	kprint("\n\tpte: ");
	put_int((unsigned long)temp_pte,16);
	kprint("\t\tpde: ");
	put_int((unsigned long)temp_pde,16);

	kprint("\n\t");
	put_int(count,10);
	kprint(" pages translated from physical to virtual address space\n");
#endif

	write_cr3(temp_pde);
	asm("cli");
	write_cr0(read_cr0() | 0x80000000);

#ifdef DEBUG_MM
	kprint("paging succesfully enabled\n");
#endif
}

//void *mm_paging_pde_new()
//sets up a valid pde table, with one pte.  The pde is self-mapped to it's physical address in the pde
void *mm_paging_pde_new() {
	unsigned long *temp_pde;
	//unsigned long *temp_pte;
	int i;

	//allocate a new physical page that the pde will be located at
	temp_pde = (unsigned long*)mm_physical_page_alloc();
	//temp_pte = (unsigned long*)mm_physical_page_alloc();

	//mark every pde entry as not-present
	for(i=0; i<1024; i++)
		temp_pde[i] = 0 | 2;
	
	//temp_pde[0] = (unsigned long)temp_pte;
	//temp_pde[0] |= 3; //the first table entry IS present

	//temp_pde[
	return temp_pde;

}

//inserts a pte in the current pde
//will be inserted to the first 'not present' entry
void *mm_paging_pde_insert() {
	unsigned long *current_pde, *temp_pte;
	int i;

	current_pde = (unsigned long*)read_cr3();
	temp_pte = (unsigned long*) mm_physical_page_alloc();

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
	
	kprint("ERROR: Unable to insert a page table into the current page directory");
	while(1);
	//return mm_physical_pages_alloc();
}

