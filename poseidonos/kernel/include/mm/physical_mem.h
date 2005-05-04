#ifndef PHYSICAL_MEM_H
#define PHYSICAL_MEM_H

#include <util/stack.h>

typedef struct mm_physical_zones
{
	long dma;
	long lowmem;
} mm_physical_zones;

#endif

