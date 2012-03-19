/* PoseidonOS v.1
    File: scheduling.h
 	(c) 2004 Tyler Southwick
	Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)*/
    
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <multitasking/multitasking.h>

void scheduler_isr(void);
int schedule();
void schedule_start(process_t *task);

#endif
