/************************************************
	sleep.c
*************************************************/

#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

extern process_t *current_process;

void sleep(int mill)
{
	asm("cli");
	current_process->process_sleep = mill;
	asm("sti");
	while(current_process->process_sleep > 0);
}
