/*******************************************************************************
* PoseidonOS v.1
* File: multitasking.c
* (c) Tyler Southwick
* Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)
*******************************************************************************/

#include <ktypes.h>
#include <kdebug.h>

#include <scheduler.h>						/*imports scheduler definitions and prototypes*/
#include <tasks.h>								/*includes prototypes for two dummy tasks*/
#include <irq.h>
#include <multitasking.h>
#include <mm/virtual_mem.h>
#include <screen.h>
#include <string.h>
#include <idt.h>
#include <mm/paging.h>

struct process_queue_item *processes;		/*the pointer to the currently running queue item*/
process_t *current_process;

/*the global system_tss*/
tss_t system_tss;

extern void kernel_init(void);
void idle_loop(void);

void idle_loop(void)
{
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

void multitasking_init() {
	process_t *idle_task;
	process_t *kernel_task;

	//reprogram pit
#ifdef DEBUG_MULTITASKING
	kprint("\nReprogramming pit...");
#endif
	
	pit_setup(100);

#ifdef DEBUG_MULTITASKING
	kprint("ok\n");
#endif
	
#ifdef DEBUG_MULTITASKING
	kprint("get tss descriptor: ");
	put_int(gdt_get_selector(gdt_tss), 10);
	kprint("\n");
#endif
	//setup system tss
	system_tss.esp0 = read_esp();
	system_tss.cr3 = read_cr3();
	setup_tss(gdt_tss);
	
	///create system idle task
	idle_task = multitasking_process_new(idle_loop, "idle task", PRIORITY_LOW, DPL_RING0);
	
	///add the two test processes to the process queue
	///the first process has to be added manually
	///by creating the process queue
	processes = kmalloc(sizeof(struct process_queue_item));
	processes->next = processes;
	processes->prev = processes;
	processes->pid = idle_task;
	
	///at the moment this is a waste of memory
	current_process = kmalloc(sizeof(process_t));
	memset(current_process, sizeof(process_t), 0);
	
	///create the kernel task
	kernel_task = multitasking_process_new(kernel_init, "kernel_init", PRIORITY_LOW, DPL_RING0);
	multitasking_process_add(kernel_task);
	
	///load the scheduler ISR into the IDT
	idt_interrupt_add(0x20, scheduler_isr, 0);
	
	asm volatile ("sti");
	irq_umask(IRQ_0);

	while(1);	
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

	if (dpl == PROCESS_USER)
	{
		code_selector = gdt_user_code | dpl;
		data_selector = gdt_user_data | dpl;
	} else {
		code_selector = gdt_kernel_code | dpl;
		data_selector = gdt_kernel_data | dpl;
	}
	
	//create a new process
	temp_process = (process_t *)kmalloc(sizeof(process_t));
	
	//setup process' stack values
	temp_stack = (unsigned int*)((unsigned int)kmalloc(MULTITASKING_UPROCESS_STACK_SIZE) + MULTITASKING_UPROCESS_STACK_SIZE);
	*temp_stack--;
	*temp_stack--=(unsigned int)task_cleanup;
	*temp_stack--=0x0202;								//EFlags
	*temp_stack--=code_selector;									//CS
	*temp_stack--=(unsigned int)handler;				//EIP
	*temp_stack--=0xEA;									//eax
	*temp_stack--=0xEC;									//ecx
	*temp_stack--=0xED1;									//edx
	*temp_stack--=0xEB1;									//ebx
	*temp_stack--;										//increment esp by 4
	*temp_stack--=0xEB2;									//ebp
	*temp_stack--=0xE2;									//esi
	*temp_stack--=0xED2;									//edi
	*temp_stack--=data_selector;									//ds
	*temp_stack--=data_selector;									//es
	*temp_stack--=data_selector;									//fs
	*temp_stack=data_selector;									//gs
	
	temp_process->esp=(unsigned int)temp_stack;
	temp_process->ss=data_selector;
	temp_process->priority=priority;
	temp_process->timetorun=priority*PRIORITY_TO_TIMETORUN;

	/*create the new address_space for the process*/
	//temp_process->cr3 = mm_virtual_mem_new_address_space();;
	
	strcpy(temp_process->name, pname);
	
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
	asm volatile("cli");		//disable interrupts so that no task switch occurs
	kfree((unsigned int*)(pid->esp));
	kfree(pid);
	
	/*remove from system queue*/
	temp_queue = processes;
	while(temp_queue->pid != pid)
		temp_queue = temp_queue->next;
	
	temp_queue->prev->next = temp_queue->next;
	temp_queue->next->prev = temp_queue->prev;
	kfree(temp_queue);
	
	asm volatile("sti");		//enable task switch
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
	asm volatile("cli");

	/*allocate space for the new queue item*/
	new_queue_item = kmalloc(sizeof(struct process_queue_item));
	
	/*set up pointers*/
	current_process_queue_item = processes;
	next = processes->next;

	/*add the proccess pid to the system queue*/
	new_queue_item->pid = pid;
	
	/*add the queue item to the queue*/
	current_process_queue_item->next = new_queue_item;
	next->prev = new_queue_item;
	new_queue_item->prev = current_process_queue_item;
	new_queue_item->next = next;
	
	/*re-enable interrupts so that task switch WILL occur*/
	asm volatile("sti");
}

void task_cleanup()
{	
	multitasking_process_kill(current_process);
	
	/*this point should never be reached
	 * The task should be destroyed sometime
	 * during this infinite loop*/
	while(1);	
}
