/* PoseidonOS v.1
    File: multitasking.h
 	(c) 2004 Tyler Southwick
	Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)*/

#ifndef MULTITASKING_H
#define MULTITASKING_H

#include <ktypes.h>
#include <kmalloc.h>
#include <gdt.h>

//constants
#define MULTITASKING_UPROCESS_STACK_SIZE 2048
#define MULTITASKING_KPROCESS_STACK_SIZE 1024

/*priority levels*/
#define PRIORITY_LOW			1
#define PRIORITY_NORMAL			2
#define PRIORITY_HIGH			3

/*dpl levels*/
#define DPL_RING0			0
#define DPL_RING1			1
#define DPL_RING2			2
#define DPL_RING3			3

#define PROCESS_DRIVER	DPL_RING0
#define PROCESS_USER		DPL_RING3

//#define

#define PRIORITY_TO_TIMETORUN	4

//define multitasking structures and types
typedef struct {
	unsigned int esp;			//position of process' esp
	unsigned int ss;			//stack segment
	unsigned int stack;		//top of process' stack
	unsigned long *cr3;
	unsigned int number;
	unsigned int parent;
	unsigned int owner;
	unsigned int group;
	unsigned int timetorun;
	unsigned int sleep;
	unsigned int priority;
	unsigned int filehandle;
	kmalloc_free *kmalloc_freelist;
	unsigned char name[32];
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
} __attribute__ ((packed)) tss_t;

struct process_queue_item {
	process_t *pid;
	struct process_queue_item *prev, *next;
};

typedef struct process_queue_item_t process_queue_item;

//define prototypes for multitasking functions
void multitasking_init(void);
process_t *multitasking_process_new(void *, char *, int, int);
void multitasking_process_kill(process_t *);
void multitasking_process_add(process_t *);
void task_cleanup(void);
void sleep(int);
void pit_setup(int);
void setup_tss(int);

#endif
