/* PoseidonOS v.1
    File: multitasking.h
 	(c) 2004 Tyler Southwick
	Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)*/

#ifndef MULTITASKING_H
#define MULTITASKING_H

#include <ktypes.h>
#include <kmalloc.h>

//constants
#define MULTITASKING_UPROCESS_STACK_SIZE 1024*3
#define MULTITASKING_KPROCESS_STACK_SIZE 1024

/*priority levels*/
#define PRIORITY_LOW			1
#define PRIORITY_NORMAL			2
#define PRIORITY_HIGH			3

#define PRIORITY_TO_TIMETORUN	4

//define multitasking structures and types
typedef struct {
	unsigned int process_esp;			//position of process' esp
	unsigned int process_ss;			//stack segment
	unsigned int process_stack;		//top of process' stack
	unsigned int process_cr3;
	unsigned int process_number;
	unsigned int process_parent;
	unsigned int process_owner;
	unsigned int process_group;
	unsigned int process_timetorun;
	unsigned int process_sleep;
	unsigned int process_priority;
	unsigned int process_filehandle;
	kmalloc_free *kmalloc_freelist;
	unsigned char process_name[32];
} process_t;

typedef struct {
	unsigned short	backlink, __blh;
	unsigned int	esp0;
	unsigned short	ss0, __ss0h;
	unsigned int	esp1;
	unsigned short	ss1, __ss1h;
	unsigned int	esp2;
	unsigned short	ss2, __ss2h;
	unsigned int	cr3;
	unsigned int	eip;
	unsigned int	eflags;
	unsigned int	eax, ecx, edx, ebx;
	unsigned int 	esp, ebp, esi, edi;
	unsigned short	es, __esh;
	unsigned short	cs, __csh;
	unsigned short	ss, __ssh;
	unsigned short	ds, __dsh;
	unsigned short	fs, __fsh;
	unsigned short	gs, __gsh;
	unsigned short	ldt, __ldth;
	unsigned short	trace, bitmap;
} tss_t;

struct process_queue_item {
	process_t *pid;
	struct process_queue_item *prev, *next;
};

typedef struct process_queue_item_t process_queue_item;

//define prototypes for multitasking functions
void multitasking_init();
process_t *multitasking_process_new(void (*handler)(), char *pname, int priority);
void multitasking_process_kill(process_t *pid);
void multitasking_process_add(process_t *pid);
void task_cleanup();
void sleep(int mill);
void pit_setup(int freq);

#endif
