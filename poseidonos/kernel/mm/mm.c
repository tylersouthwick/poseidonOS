/* File: mm.c
   Description: implement the system memory manager*/

#include <ktypes.h>
#include <kdebug.h>

#include <mm/mm.h>
#include <mm/paging.h>
#include <mm/multiboot.h>
#include <mm/sbrk.h>
#include <mm/physical_mem.h>
#include <mm/virtual_mem.h>

unsigned long floppy_dma_address;

void mm_init(multiboot_info_t *mm_info)
{
	//create a bitmap of available physical pages
	mm_physical_pages_init(mm_info);

	//enable paging
	mm_paging_init();

	//setup sbrk()
	sbrk_init();
	
	/*this is only a temporary fix until something is setup to allocate DMA addresses*/
	//floppy_dma_address = mm_physical_page_alloc(MM_TYPE_DMA);
}
