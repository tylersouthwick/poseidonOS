#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <mm/mm.h>
#include <mm/virtual_mem.h>
#include <mm/sbrk.h>

int page_offset;	//number of bytes offset in the page that the next block can start from
static page_t current_vpage;

void sbrk_init() {
	page_offset = 0;

	//set up a new page table entry as the first one for sbrk
	current_vpage.count = 1; 
	mm_virtual_page_alloc(&current_vpage);
}

void *sbrk(unsigned int nBytes) {
	int offset_buffer;

	//kprint("sbrk...\n");
	//is this block of memory going to fit in the current page?
	if (nBytes + page_offset > 4096) {
		//no
		/*eventually this will create a continuous block
		  but, right now, it will just allocate a new page
		  and start from there.  Very ineffiencent*/
		mm_virtual_page_alloc(&current_vpage);
		page_offset = (int)nBytes;
		return (void *)(current_vpage.address);
	} else {
		void *addr;

		//just increase the offset counter
		offset_buffer = page_offset;
		page_offset += (int)nBytes;
		addr = (void *)((unsigned long)(current_vpage.address) + offset_buffer);

		return addr;
	}
}

