#include <mm.h>
#include <physical_mem.h>
#include <string.h>
#include <screen.h>

int p_page_count;
unsigned char *mm_physical_bitmap;

//physical bitmap macros
//ADR: returns the physical address given two indexes
//#define MM_PHYSICAL_BITMAP_ADR(a,b) (((a << 3) + b) << 12)
//SP: returns the superpage index of a given physical page
//#define MM_PHYSICAL_BITMAP_SP(a) (a >> 15)
//SB: returns the subpage index of a given physical page
//#define MM_PHYSICAL_BITMAP_SB(a) ((a >> 12) % 8)

void mm_physical_pages_init(multiboot_info_t *mm_info) {
	int buffer;
	//memory_map_t *mmap;
	//unsigned long address = 0;
	unsigned int i,h;
	//unsigned char *buffer1;

	kprint("There is ");
	put_int(mm_info->mem_upper, 10);
	kprint("kb of memory.\n");
	p_page_count = (mm_info->mem_upper)/4;
	put_int(p_page_count, 10);
	kprint(" pages found.\n");
	put_int(p_page_count/8,10);
	kprint(" superpages created");

	mm_physical_bitmap = (unsigned char*)kernel_end;//(0xFFFFF-page_count/8);
	end_of_kernel = ((int)kernel_end+(((int)p_page_count/8))); //pagealign 
	end_of_kernel &= 0xFFFFF000;

	if (end_of_kernel < (int)kernel_end+p_page_count/8)
		end_of_kernel += 4096;

	kprint("\n(int)kernel_end+p_page_count/8 = ");
	put_int((int)kernel_end+p_page_count/8, 16);
	kprint("\nend_of_kernel = ");
	put_int(end_of_kernel,16);

	/*mm_physical_bitmap:
	This table will be a char array, with each bit of each char element
	pointing to a different page.  This is similar to cottontail
	memory management's 'supertables'.  If any of the elements != 0 then
	there has to be at least ONE free page.  This will then be determined
	with some sort of algorithm.

	once the index to a free page in the table is discovered, the physical
	address will be at:
		((superpage_index << 3) +subpage_index) << 12
	
	This will return a page aligned physical memory address. 
		
	*/

	/*initilize mm_physical_bitmap using the memory map provided by grub
	  plus the known size of the kernel */
	memset(mm_physical_bitmap, 0, p_page_count/8);
	memset(mm_physical_bitmap, 255, end_of_kernel/(4096*8));
	memset(mm_physical_bitmap + (end_of_kernel/(4096*8)), 1, 1);

	//clear_screen();
	kprint("\nnumber of pages allocated: ");
	put_int((((int)end_of_kernel)/4096),10);
	//while(1);

	kprint("\nPhysical Memory bitmap created at ");
	put_int((int)mm_physical_bitmap, 16);
	buffer = 0;

//clear_screen();	
	//count the number of allocated pages
	for (i=0; i<p_page_count/8; i++) { 
		if (mm_physical_bitmap[i] != 0) {
			for (h=0; h<8; h++) {
				if ((mm_physical_bitmap[i] >> h) & 1)
					buffer++;
			}
		}
	}
//while(1);
	put_char('\n');
	put_int(buffer,10);
	kprint(" physical page(s) marked as 'present'\n");
}

//need to figure out a better algorithm that is more efficient
//ideas: superpages ?
void *mm_physical_page_alloc() {
	int superpage_index, subpage_index, buffer;

	//find a free superpage page
	for (superpage_index=0; superpage_index<p_page_count/8; superpage_index++) {
		if (mm_physical_bitmap[superpage_index] != 255)
			//find a free subpage
			for (subpage_index = 0; subpage_index < 8; subpage_index++) {
				buffer = mm_physical_bitmap[superpage_index];
				buffer = buffer >> subpage_index;
				buffer = buffer & 0x1;
				if (buffer == 0) {
					mm_physical_bitmap[superpage_index] |= (1 << subpage_index);
					return (void*)MM_PHYSICAL_BITMAP_ADR(superpage_index, subpage_index);
				}
			}
	}
	
	/*if no physical page was found, out of memory.
	  Eventually this will add support for a swap
	  file or disk.  But right now, the system will
	  enter an infinite loop*/
	kprint("SYSTEM ERROR: NO FREE MEMORY!");
	while(1);
}

void mm_physical_page_free(void *p_addr) {
	int superpage_index, subpage_index;

	//get indexes
	superpage_index = MM_PHYSICAL_BITMAP_SP((int)p_addr);
	subpage_index   = MM_PHYSICAL_BITMAP_SB((int)p_addr);
	
	//set page index to 0 -> 'not present'
	mm_physical_bitmap[superpage_index] = mm_physical_bitmap[superpage_index] & (0xFF ^ (1 << subpage_index)); 
}
