/* PoseidonOS v.1
    File: scheduling.c
 	(c) 2004 Tyler Southwick
	Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)*/

#include <ktypes.h>
#include <kdebug.h>

#include <core/irq.h>
#include <multitasking/scheduler.h>
#include <mm/paging.h>
#include <multitasking/multitasking.h>

extern struct process_queue_item *processes;		/*the pointer to the currently running queue item*/
process_t *current_process;

int millisecond_count = 0;
int second_count = 0;
int timer_count = 0;

void floppy_timer(void);
int get_current_process(void);

static void starting_task() {
	while(1);
}

void schedule_start(process_t *task) {
	DEBUG(("starting scheduler"));
	current_process = multitasking_process_new(starting_task, "starting task", PRIORITY_LOW, DPL_RING0);
	irq_umask(IRQ_0);
	__asm__ volatile ("sti");

	while(1);	
}

int schedule(long system_timer_ms)
{
	//DEBUG(("called system timer: %s", current_process->name));
	
	///check to see if the process is finished with its timeslice
	if (current_process->timetorun-- <= 0)
	{
		///reset the current process' time to run count
		current_process->timetorun = (current_process->priority)*PRIORITY_TO_TIMETORUN;
		
		///look through the process queue until a non-sleeping thread is found
		processes = processes->next;
		while (processes->pid->sleep > 0)
		{
			processes->pid->sleep--;
			processes = processes->next;
		}
		///when found, point current_process to the
		///non-sleeping thread
		current_process = processes->pid;	
		//DEBUG(("switched process: %s [stack: @0x%x]", current_process->name, current_process->esp));

		//change cr3
#ifdef CHANGE_CR3
		//write_cr3(current_process->cr3);
#endif
	}
	
	///the new esp must be passed back to the scheduler isr!
	return current_process->esp;
}

/***************Timer stuff********************/

