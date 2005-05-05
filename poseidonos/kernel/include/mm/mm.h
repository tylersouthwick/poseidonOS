/* File: mm.h
   Description: define memory manager prototypes and structures*/

#ifndef MM_H
#define MM_H

#include <mm/multiboot.h>

#include <mm/physical_mem.h>

//general mm stuff
void mm_init(multiboot_info_t *mm_info);

//virtual mm
void mm_physical_pages_init(multiboot_info_t *mm_info);
void mm_paging_init();

#define kernel_start 0x100000
#define kernel_end   0x140000

int end_of_kernel;
//only for debugging purposes:
//#define MM_VIRTUAL_MEM_DEBUG
//#define MM_KMALLOC_DEBUG
//#define MM_PAGING_DEBUG
//#define MM_KFREE_DEBUG

#define size_t int

#define USER_SPACE_START	512

#endif

