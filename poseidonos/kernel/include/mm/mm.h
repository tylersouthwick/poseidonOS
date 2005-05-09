/* File: mm.h
   Description: define memory manager prototypes and structures*/

#ifndef MM_H
#define MM_H

#include <mm/multiboot.h>

#include <mm/physical_mem.h>

//general mm stuff
void mm_init(multiboot_info_t *);

//virtual mm
void mm_paging_init(void);

#define kernel_start 0x100000
#define kernel_end   0x140000

#define USER_SPACE_START	512

#endif

