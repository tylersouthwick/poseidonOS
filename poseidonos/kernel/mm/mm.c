/* File: mm.c
   Description: implement the system memory manager*/

#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <paging.h>
#include <multiboot.h>
#include <sbrk.h>

unsigned long floppy_dma_address;

void mm_init(multiboot_info_t *mm_info)
{
	/* Print out the flags. */
#ifdef DEBUG_MM
  kprint ("flags = ");
  put_int((unsigned) mm_info->flags, 16);
  put_char('\n');

  // Are mem_* valid?
  if (CHECK_FLAG (mm_info->flags, 0))
    kprint ("mem_lower = ");
    put_int((unsigned) mm_info->mem_lower, 16);
	kprint("KB, mem_upper = ");
	put_int((unsigned) mm_info->mem_upper,16);
	kprint("KB\n");

  // Is boot_device valid?
  if (CHECK_FLAG (mm_info->flags, 1))
    kprint ("boot_device = ");
	put_int((unsigned) mm_info->boot_device,10);
	put_char('\n');
  
  // Is the command line passed?
  if (CHECK_FLAG (mm_info->flags, 2))
    kprint ("cmdline = ");
    kprint((char *) mm_info->cmdline);
	put_char('\n');

#endif
  // Are mmap_* valid? */
  if (CHECK_FLAG (mm_info->flags, 6))
    {
      memory_map_t *mmap;
      
#ifdef DEBUG_MM
      kprint ("mmap_addr = ");
	  put_int((unsigned) mm_info->mmap_addr,16);
	  kprint(" mmap_length = ");
	  put_int((unsigned) mm_info->mmap_length,16);
	  put_char('\n');
	  
      for (mmap = (memory_map_t *) mm_info->mmap_addr; mmap < mm_info->mmap_addr + mm_info->mmap_length;
           mmap = (memory_map_t *) ((unsigned long) mmap
                                    + mmap->size + sizeof (mmap->size)))
        kprint ("size = ");
		put_int ((unsigned) mmap->size,16);
		kprint( ", base_addr = ");
		put_int((unsigned) mmap->base_addr_high,16);
		put_int((unsigned) mmap->base_addr_low,16);
		kprint(", length = ");
		put_int((unsigned) mmap->length_high,16);
		put_int((unsigned) mmap->length_low,16);
		kprint(", type = ");
		put_int((unsigned) mmap->type,16);
		put_char('\n');
#endif
	}

	//create a bitmap of available physical pages
	mm_physical_pages_init(mm_info);
	//enable paging
	mm_paging_init();
	//setup sbrk()
	sbrk_init();
	
	/*this is only a temporary fix until something is setup to allocate DMA addresses*/
	floppy_dma_address = 0x5000;
}
