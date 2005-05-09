#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <mm/mm.h>
#include <mm/virtual_mem.h>
#include <mm/sbrk.h>

int page_offset;	//number of bytes offset in the page that the next block can start from
unsigned static long *current_vpage;

void sbrk_init() {
	page_offset = 0;

	//set up a new page table entry as the first one for sbrk
	current_vpage = (unsigned long*)mm_virtual_page_alloc();
	/*
	kprint("sbrk_init :: current_vpage -> ");
	put_int(current_vpage, 0x10);
	kprint("\n");
	kprint("testing....");
	page_offset = current_vpage[0];
	kprint("ok\n");
	page_offset = 0;
	*/
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
	//	kprint("get a new virtual page...");
		current_vpage = (unsigned long*)mm_virtual_page_alloc();
//		kprint("ok\n");
		page_offset = (int)nBytes;
		return (void *)(current_vpage);
	} else {
		void *addr;

		//just increase the offset counter
		offset_buffer = page_offset;
		page_offset += (int)nBytes;
		addr = (void *)((int)current_vpage + offset_buffer);

		/*
		kprint("addr: ");
		put_int(addr, 0x10);
		kprint("\n");
		*/

		return addr;
	}
}

