/* File: mm.h
   Description: define memory manager prototypes and structures*/

//multiboot stuff
#include <multiboot.h>

#ifndef MM_H
#define MM_H

//general mm stuff
void mm_init(multiboot_info_t *mm_info);

//physical memory manager
void *mm_physical_page_alloc();
void mm_physical_page_free(void *p_addr);
void *mm_virtual_page_alloc();
void mm_virtual_page_free(void *v_addr);
int p_page_count;
unsigned char *mm_physical_bitmap;


//virtual mm
void mm_physical_pages_init(multiboot_info_t *mm_info);
void mm_paging_init();

typedef struct mm_page_header {
	unsigned long bitmap[4];
	void *next;
} mm_page_header_t;

#define kernel_start 0x100000
#define kernel_end   0x140000

int end_of_kernel;
//only for debugging purposes:
//#define MM_VIRTUAL_MEM_DEBUG
//#define MM_KMALLOC_DEBUG
//#define MM_PAGING_DEBUG
//#define MM_KFREE_DEBUG

//macros
//ADR: returns the physical address given two indexes
#define MM_PHYSICAL_BITMAP_ADR(a,b) (((a << 3) + b) << 12)
//SP: returns the superpage index of a given physical page
#define MM_PHYSICAL_BITMAP_SP(a) (a >> 15)
//SB: returns the subpage index of a given physical page
#define MM_PHYSICAL_BITMAP_SB(a) ((a >> 12) % 8)

#define size_t int

#endif

