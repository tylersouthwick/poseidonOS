/* PoseidonOS v.1
    File: scheduling.c
 	(c) 2004 Tyler Southwick
	Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)*/

#include <multitasking.h>
#include <scheduler.h>
#include <screen.h>

extern struct process_queue_item *processes;		/*the pointer to the currently running queue item*/
extern process_t *current_process;

int system_time = 0;
int timer_count = 0;

void floppy_timer();

int getCurrentProcess()
{
	system_time++;
	if (system_time > 100)
	{
		put_int(timer_count++, 10);
		put_char(32);
		system_time = 0;
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

