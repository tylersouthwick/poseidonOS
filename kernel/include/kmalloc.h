#include <ktypes.h>

#ifndef KMALLOC_H
#define KMALLOC_H

//kmalloc struct
typedef struct kmalloc_free_type kmalloc_free;

struct kmalloc_free_type {
	int size;
	kmalloc_free *prev, *next;
};

void *kmalloc(unsigned int nBytes); 
void kfree(void *addr);

#endif

