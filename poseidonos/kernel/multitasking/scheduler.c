/* PoseidonOS v.1
    File: scheduling.c
 	(c) 2004 Tyler Southwick
	Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)*/

#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <scheduler.h>

extern struct process_queue_item *processes;		/*the pointer to the currently running queue item*/
extern process_t *current_process;

int millisecond_count = 0;
int second_count = 0;
int timer_count = 0;

void floppy_timer(void);
int get_current_process(void);

int get_current_process()
{
	millisecond_count++;
	if (millisecond_count > 100)
	{
		millisecond_count = 0;
		second_count++;
	}
	
	///check to see if the process is finished with its timeslice
	if (current_process->process_timetorun-- <= 0)
	{
		///reset the current process' time to run count
		current_process->process_timetorun = (current_process->process_priority)*PRIORITY_TO_TIMETORUN;
		
		///look through the process queue until a non-sleeping thread is found
		processes = processes->next;
		while (processes->pid->process_sleep > 0)
		{
			processes->pid->process_sleep--;
			processes = processes->next;
		}
		///when found, point current_process to the
		///non-sleeping thread
		current_process = processes->pid;	
	}
	
	///the new esp must be passed back to the scheduler isr!
	return current_process->process_esp;
}

/***************Timer stuff********************/

