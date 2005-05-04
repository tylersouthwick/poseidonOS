#ifndef PHYSICAL_MEM_H
#define PHYSICAL_MEM_H

#include <util/stack.h>

struct mm_physical_zones
{
	stack_t dma;
	stack_t lowmem;
}

#endif

