#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <mm/mm.h>

int page_offset;	//number of bytes offset in the page that the next block can start from
unsigned long *current_vpage;

void sbrk_init() {
	page_offset = 0;

	//set up a new page table entry as the first one for sbrk
	current_vpage = (unsigned long*)mm_virtual_page_alloc();
}

void *sbrk(unsigned int nBytes) {
	int offset_buffer;
	//is this block of memory going to fit in the current page?
	if (nBytes + page_offset > 4096) {
		//no
		/*eventually this will create a continuous block
		  but, right now, it will just allocate a new page
		  and start from there.  Very ineffiencent*/
		current_vpage = (unsigned long*)mm_virtual_page_alloc();
		page_offset = (int)nBytes;
		return (void *)(current_vpage);
	} else {
		//just increase the offset counter
		offset_buffer = page_offset;
		page_offset += (int)nBytes;
		return (void *)((int)current_vpage + offset_buffer);
	}
}

