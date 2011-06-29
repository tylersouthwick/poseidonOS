#include <ktypes.h>
#include <kdebug.h>

#include <mm/sbrk.h>
#include <kmalloc.h>

kmalloc_free *free_mem=(kmalloc_free*)0;					/*the free memory linked list.  When memory is free'd it is hooked onto this list*/

/********************************************************************************
 * void *kmalloc(size_t nBytes)
 * 
 * Allocates nBytes+sizeof(kmalloc_free) of heap memory for the calling kernel process.
 * sizeof(kmalloc_free) is added to nBytes to provide the memory chunk with a header
 * First, tt searches through the free memory linked and sees if there is any chunk that
 * is at least as big as nBytes. If a chunk is found, that chunk is removed from the
 * free_mem list and returned to the process as a pointer.  If no chunk is found, then
 * another chunk is created by calling sbrk().
 * 
 * Parameter:
 * 	1) size_t nBytes
 * 		The amount of memory requested.
 * 
 * Return value:
 * 	Valid pointer - on success
 * 	-1 - on error
 * 
 * Author : Tyler Southwick (northfuse@gmail.com)
 * Date     : September 16, 2004
 * ******************************************************************************/
 
void *kmalloc(unsigned int nBytes) {
	kmalloc_free *free_mem_temp;		/*temporary pointer to the free memory list- allows the list to be traversed*/
	kmalloc_free *chunk_start;		/*stores the beginning of the memory to be returned by kmalloc*/
	kmalloc_free *prev;			/*used as a temporary holder while traversing the free memory list*/
	kmalloc_free *next;			/*used as a temporary holder while traversing the free memory list*/
	
	nBytes += sizeof(struct kmalloc_free_type); //add enough space for the header

	free_mem_temp = free_mem;
	while(free_mem_temp != 0) {
		//check to see if there is suffient mem space in this chunk
		if (free_mem_temp->size > nBytes) {
			//remove this item from the list
			prev = free_mem_temp->prev;
			next = free_mem_temp->next;
			prev->next = next;
			next->prev = prev;
			chunk_start = free_mem_temp;
			
			chunk_start->prev = 0;
			chunk_start->next = 0;

			void *addr = (void *)((int)chunk_start + sizeof(struct kmalloc_free_type));
			DEBUG(("returning %i bytes @0x%x", nBytes, addr));
			return addr;
		}

		free_mem_temp = free_mem_temp->next;
	}

	//there wasn't suffient mem space in any chunk
	chunk_start = (kmalloc_free *)sbrk(nBytes);
	chunk_start->size = nBytes;
	chunk_start->prev = 0;
	chunk_start->next = 0;

	return (void *)((int)chunk_start+sizeof(struct kmalloc_free_type));
}

/********************************************************************************
 * void free(void *addr)
 * 
 * free's the memory allocated by kmalloc().  The memory is added to the free memory
 * linked list.
 * 
 * Parameters:
 * 	1) void *addr
 * 		The pointer returned by kmalloc()
 * 
 * Return value:
 * 	none
 * 
 * Author : Tyler Southwick (northfuse@gmail.com)
 * Date     : September 16, 2004
 * *****************************************************************************/
void kfree(void *addr) {
	//kmalloc_free *free_mem_temp;
	kmalloc_free *freed_adr;
	//unsigned long *buffer;
	//kmalloc_free *previous;
	kmalloc_free *current;
	
	current = free_mem;
	freed_adr = addr;
	
	if (current == 0) { //no items in list
		current = addr;
		current->next = 0;
		current->prev = 0;
		return;
	}
	
	while (current->next != 0) {
		current  = current->next;
	}
	
	freed_adr->next = 0;
	freed_adr->prev = current;
	current->next = addr;
	
	return;
}

