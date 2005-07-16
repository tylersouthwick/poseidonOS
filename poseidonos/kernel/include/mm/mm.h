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

/*these are linker script symbols*/
extern int _kernel_start;
extern int _kernel_end;
#define KERNEL_START ((unsigned int)&_kernel_start)
#define KERNEL_END   ((unsigned int)&_kernel_end)

#define USER_SPACE_START	512

#endif

