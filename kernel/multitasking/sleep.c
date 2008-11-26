/************************************************
	sleep.c
*************************************************/

#include <ktypes.h>
#include <kdebug.h>

#include <multitasking.h>

extern process_t *current_process;

void sleep(int mill)
{
	asm volatile("cli");
	current_process->sleep = mill;
	asm volatile("sti");
	while(current_process->sleep > 0);
}
