#ifndef PHYSICAL_MEM_H
#define PHYSICAL_MEM_H

#include <util/stack.h>

/**************************************
 * constants
 * ***********************************/

#define MM_TYPE_DMA	0
#define MM_TYPE_NORMAL 1

/**************************************
 * macros
 * ***********************************/
//ADR: returns the physical address given two indexes
#define MM_PHYSICAL_BITMAP_ADR(a,b) (((a << 3) + b) << 12)
//SP: returns the superpage index of a given physical page
#define MM_PHYSICAL_BITMAP_SP(a) (a >> 15)
//SB: returns the subpage index of a given physical page
#define MM_PHYSICAL_BITMAP_SB(a) ((a >> 12) % 8)

/**************************************
 * structures
 **************************************/
typedef struct mm_physical_page_zones
{
	unsigned char *dma_bitmap;
	unsigned int dma_page_count;
	unsigned char *normal_bitmap;
	unsigned int normal_page_count;
} mm_physical_page_zones;

typedef struct mm_page_header {
	unsigned long bitmap[4];
	void *next;
} mm_page_header_t;

/**************************************
 * prototypes
 **************************************/
void mm_physical_pages_init(multiboot_info_t *mm_info);
void *mm_physical_page_alloc(int type);
void mm_physical_page_free(void *p_addr);

#endif

