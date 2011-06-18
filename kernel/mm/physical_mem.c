#include <ktypes.h>
#include <kdebug.h>

#include <mm/physical_mem.h>
#include <string.h>
#include <screen.h>

mm_physical_page_zones memory_zones;

void *mm_physical_page_alloc_dma(void);
void *mm_physical_page_alloc_normal(void);

void mm_physical_pages_init(multiboot_info_t *mm_info) {
	int page_count;
	int end_of_kernel = KERNEL_END;

	page_count = (mm_info->mem_upper)/4;

	DEBUG(("Creating %i physical pages"));

	memory_zones.dma_page_count = 4096; /*16 MB of 4KB pages*/
	if (memory_zones.dma_page_count > page_count)
	{
		memory_zones.dma_page_count = page_count;
		memory_zones.normal_page_count = 0;
	} else
		memory_zones.normal_page_count = page_count - memory_zones.dma_page_count;

	/*append the dma bitmap onto the end of the kernel
	 * and the normal bitmap after the dma bitmap*/
	memory_zones.dma_bitmap = (unsigned char*)end_of_kernel;
	memory_zones.normal_bitmap = (unsigned char*)((int)memory_zones.dma_bitmap + (memory_zones.dma_page_count >> 3));

	/*adjust end of kernel counter
	 * pages are added to the end of the kernel image */
	end_of_kernel += (unsigned int)(page_count/8);
	end_of_kernel &= 0xFFFFF000;
	end_of_kernel++;

	/*initilize physical bitmaps*/
	memset(memory_zones.dma_bitmap, 0, page_count/8);
	memset(memory_zones.dma_bitmap, 255, end_of_kernel/(4096*8) + 1);
}

void *mm_physical_page_alloc(int type) {
	long *page;

	switch (type)
	{
		case MM_TYPE_DMA:
			if (!(page = mm_physical_page_alloc_dma()))
				goto mm_physical_page_alloc_error;
			return page;
		default:
			if (!(page = mm_physical_page_alloc_normal()))
				goto mm_physical_page_alloc_error;
			return page;
	}
mm_physical_page_alloc_error:
	__asm__ volatile ("cli");
	ERROR(("error allocating page!"));
	while(1);
}

void *mm_physical_page_alloc_normal()
{
	int superpage_index, subpage_index, buffer;

	for (superpage_index=0; superpage_index<memory_zones.normal_page_count/8; superpage_index++) {
		if (memory_zones.normal_bitmap[superpage_index] != 255)
			//find a free subpage
			for (subpage_index = 0; subpage_index < 8; subpage_index++) {
				buffer = memory_zones.normal_bitmap[superpage_index];
				buffer = buffer >> subpage_index;
				buffer = buffer & 0x1;
				if (buffer == 0) {
					memory_zones.normal_bitmap[superpage_index] |= (1 << subpage_index);
					return (void*)MM_PHYSICAL_BITMAP_ADR(superpage_index + 512, subpage_index);
				}
			}
	}
	
	return mm_physical_page_alloc_dma();
}

void *mm_physical_page_alloc_dma()
{
	int superpage_index, subpage_index, buffer;

	for (superpage_index=0; superpage_index<memory_zones.dma_page_count/8; superpage_index++) {
		if (memory_zones.dma_bitmap[superpage_index] != 255)
			//find a free subpage
			for (subpage_index = 0; subpage_index < 8; subpage_index++) {
				buffer = memory_zones.dma_bitmap[superpage_index];
				buffer = buffer >> subpage_index;
				buffer = buffer & 0x1;
				if (buffer == 0) {
					memory_zones.dma_bitmap[superpage_index] |= (1 << subpage_index);
					return (void*)MM_PHYSICAL_BITMAP_ADR(superpage_index, subpage_index);
				}
			}
	}
	return (void *)0;
}

void mm_physical_page_free(void *p_addr) {
	//int superpage_index, subpage_index;

	DEBUG(("mm_physical_page_free :: warning -> page not free'd!\n"));

	//get indexes
	//superpage_index = MM_PHYSICAL_BITMAP_SP((int)p_addr);
	//subpage_index   = MM_PHYSICAL_BITMAP_SB((int)p_addr);
	
	//set page index to 0 -> 'not present'
	//mm_physical_bitmap_dma[superpage_index] = mm_physical_bitmap_dma[superpage_index] & (0xFF ^ (1 << subpage_index)); 
}
