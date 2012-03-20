#include <ktypes.h>
#include <kdebug.h>

#include <mm/mm.h>
#include <mm/virtual_mem.h>
#include <mm/sbrk.h>

static int page_offset;	//number of bytes offset in the page that the next block can start from
static page_t current_vpage;

void sbrk_init() {
	DEBUG_MSG(("sbrk init"));
	page_offset = 0;

	//set up a new page table entry as the first one for sbrk
	current_vpage.count = 1; 
	mm_virtual_page_alloc(&current_vpage);
}

void *sbrk(unsigned int nBytes) {
	int offset_buffer;

	DEBUG_MSG(("sbrk %i bytes", nBytes));

	//is this block of memory going to fit in the current page?
	if (nBytes + page_offset > current_vpage.count * 4096) {
		/*how many pages do we need?*/

		current_vpage.count = nBytes / 4096 + 1;
		DEBUG_MSG(("we need %i pages", current_vpage.count));
		mm_virtual_page_alloc(&current_vpage);
		page_offset = (int)nBytes;
		DEBUG_MSG(("got address: 0x%x", current_vpage.address));
		return (void *)(current_vpage.address);
	} else {
		void *addr;

		//just increase the offset counter
		offset_buffer = page_offset;
		page_offset += (int)nBytes;
		addr = (void *)((unsigned long)(current_vpage.address) + offset_buffer);

		DEBUG_MSG(("got address: 0x%x", addr));
		return addr;
	}
}

