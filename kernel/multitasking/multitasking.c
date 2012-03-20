/*******************************************************************************
* PoseidonOS v.1
* File: multitasking.c
* (c) Tyler Southwick
* Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)
*******************************************************************************/

#include <ktypes.h>
#include <kdebug.h>

#include <multitasking/scheduler.h>						/*imports scheduler definitions and prototypes*/
#include <multitasking/timer.h>
#include <core/irq.h>
#include <multitasking/multitasking.h>
#include <mm/virtual_mem.h>
#include <screen.h>
#include <string.h>
#include <core/idt.h>
#include <mm/paging.h>
#include <core/gdt.h>

struct process_queue_item *processes;		/*the pointer to the currently running queue item*/
process_t *current_process;

static void idle_loop(void);

static void idle_loop(void) {
	while(1);
}

/********************************************************************************
 * void multitasking_init()
 * 
 * Initilizes the multitasking environment.  Creates the process queue and adds the
 * kernel process to it.  Then, the scheduler interrupt is installed (via the timer interrupt
 * at irq 0).  IRQ0 is unmasked, and the scheduler is a go!
 * 
 * Parameters:
 * 	none
 * 
 * Return value:
 * 	none
 * 
 * Preconditions:
 * 	A working memory manager must be implemented that supports kmalloc() and
 * 	free().  Also, a working hook into the interrupt table functions should be available
 * 	via the idt_interrupt_install() interface.
 * 
 * Postconditions:
 * 	Process creation can now be done from multitasking_process_new()
 * ******************************************************************************/ 

void multitasking_init(void (*kernel_init)()) {
	process_t *idle_task;
	process_t *kernel_task;

	//stop interrupts, just in case
	__asm__ volatile ("cli");

	//setup timer
	timer_init();

	tss_init();

	///create system idle task
	idle_task = multitasking_process_new(idle_loop, "idle task", PRIORITY_LOW, DPL_RING0);
	
	///by creating the process queue
	processes = kmalloc(sizeof(struct process_queue_item));
	processes->next = processes;
	processes->prev = processes;
	processes->pid = idle_task;
	
	///create the kernel task
	kernel_task = multitasking_process_new(kernel_init, "kernel_init", PRIORITY_HIGH, DPL_RING0);
	multitasking_process_add(kernel_task);
	
	schedule_start(kernel_task);

	FATAL_MSG(("Shoouldn't get here"));
}

/********************************************************************************
 * process_t *multitasking_process_new(void (*handler)(), char *pname)
 * 
 * Creats a new process given the entry point of the process.  Sets up a stack and all
 * the system registers for it.  The pid is returned in the form of a process_t pointer.
 * NOTE: This does NOT add the process to the system queue.  That must be done
 * seperatly.
 * 
 * Parameters:
 *   1) void (*handler)()
 *     This is the pointer to the entry point of the process, usually its main() function.
 * 
 * Return value:
 * 	returns a pointer to a process structure, but doubles as a pid (process identification
 * 	descriptor).  This pointer is used to add the process to the system queue.
 * ******************************************************************************/
process_t *multitasking_process_new(void *handler, char *pname, int priority, int dpl) {
	process_t *temp_process;
	unsigned int *temp_stack;
	int data_selector, code_selector;

	//only while testing!
//	dpl = 0;

  /*
	if (dpl == PROCESS_USER)
	{
		code_selector = gdt_user_code | dpl;
		data_selector = gdt_user_data | dpl;
	} else {
		code_selector = gdt_kernel_code | dpl;
		data_selector = gdt_kernel_data | dpl;
	}
  */
	data_selector = 0x10;
	code_selector = 0x08;
	
	//create a new process
	temp_process = (process_t *)kmalloc(sizeof(process_t));
	
	//setup process' stack values
	temp_stack = (unsigned int*)((unsigned int)kmalloc(USTACK_SIZE) + USTACK_SIZE);
	temp_process->kstack = (int) temp_stack;
	*temp_stack--;
	*temp_stack--=(unsigned int)task_cleanup;
	*temp_stack--=0x0202;
	*temp_stack--=code_selector;
	*temp_stack--=(unsigned int)handler;		//EIP
	*temp_stack--=0;                            //ebp
	*temp_stack--=0;                            //esp
	*temp_stack--=0;                            //edi
	*temp_stack--=0;                            //esi
	*temp_stack--=0;                            //edx
	*temp_stack--=0;                            //ecx
	*temp_stack--=0;                            //ebx
	*temp_stack--=0;                            //eax
	*temp_stack--=data_selector;								//ds
	*temp_stack--=data_selector;								//es
	*temp_stack--=data_selector;								//fs
	*temp_stack=data_selector;									//gs
	
	temp_process->esp=(unsigned int)temp_stack;
	temp_process->ustack = (unsigned int)kmalloc(USTACK_SIZE) + USTACK_SIZE;
	temp_process->ss=data_selector;
	temp_process->priority=priority;
	temp_process->timetorun=priority*PRIORITY_TO_TIMETORUN;

	/*create the new address_space for the process*/
	temp_process->cr3 = read_cr3();
	
	strcpy(temp_process->name, pname);
	
	DEBUG_MSG(("created process %s [stack: @0x%x]", temp_process->name, temp_stack));
	return temp_process;
}

/********************************************************************************
 * void multitasking_process_kill(process_t *pid)
 * 
 * Kills the process by free'ing all the memory associated with it.  Once killed,
 * the process is unrecoverable.  This function will also attempt to remove the
 * pid from the system queue
 * 
 * Parameters:
 * 	1) process_t *pid
 * 		This is the pointer to the process' structure (aka its pid)
 * 
 * Return value:
 * 	none
 * ******************************************************************************/
void multitasking_process_kill(process_t *pid) {
	struct process_queue_item *temp_queue;
	
	//kill process
	__asm__ volatile("cli");		//disable interrupts so that no task switch occurs
	kfree((unsigned int*)(pid->esp));
	kfree(pid);
	
	/*remove from system queue*/
	temp_queue = processes;
	while(temp_queue->pid != pid)
		temp_queue = temp_queue->next;
	
	temp_queue->prev->next = temp_queue->next;
	temp_queue->next->prev = temp_queue->prev;
	kfree(temp_queue);
	
	__asm__ volatile("sti");		//enable task switch
}

/********************************************************************************
 * void multitasking_process_add(process_t *pid)
 * 
 * Adds the given process structure to the system queue as the next element in the
 * queue.  This allows the scheduler to call the process and give it its own time
 * at the cpu, resources, etc.  If the process is never added then the process will
 * never run!
 * 
 * Parameters:
 * 	1) process_t *pid
 * 		This is a pointer to the process' structure (aka pid)
 * 
 * Return value:
 *   none
 * ******************************************************************************/
void multitasking_process_add(process_t *pid) {
	struct process_queue_item *new_queue_item;		/*holds the pointer to process pid's queue entry*/
	//struct process_queue_item *prev;			/*holds the pointer to the previous system process*/ 
	struct process_queue_item *next;			/*holds the pointer to the next system process*/
	struct process_queue_item *current_process_queue_item;	/*holds the pointer to the entry in the system process queue*/

	/*make sure that no task switch will occur :) */
	__asm__ volatile("cli");

	DEBUG_MSG(("adding process %s", pid->name));

	TRACE_MSG(("allocate space for the new queue item"));
	new_queue_item = kmalloc(sizeof(struct process_queue_item));
	
	TRACE_MSG(("set up pointers"));
	current_process_queue_item = processes;
	next = processes->next;

	TRACE_MSG(("add the proccess pid to the system queue"));
	new_queue_item->pid = pid;
	
	TRACE_MSG(("add the queue item to the queue"));
	current_process_queue_item->next = new_queue_item;
	next->prev = new_queue_item;
	new_queue_item->prev = current_process_queue_item;
	new_queue_item->next = next;
	
	TRACE_MSG(("re-enable interrupts so that task switch WILL occur"));
	__asm__ volatile("sti");

	DEBUG_MSG(("added process %s", pid->name));
}

void task_cleanup()
{	
	DEBUG_MSG(("killing task %s", current_process->name));

	multitasking_process_kill(current_process);
	
	/*this point should never be reached
	 * The task should be destroyed sometime
	 * during this infinite loop*/
	while(1);	
}
