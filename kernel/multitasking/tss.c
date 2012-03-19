/*******************************************************************************
* PoseidonOS v.1
* File: multitasking.c
* (c) Tyler Southwick
* Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)
*******************************************************************************/

#include <ktypes.h>
#include <kdebug.h>

#include <multitasking/scheduler.h>						/*imports scheduler definitions and prototypes*/
#include <core/irq.h>
#include <multitasking/multitasking.h>
#include <mm/virtual_mem.h>
#include <screen.h>
#include <string.h>
#include <core/idt.h>
#include <mm/paging.h>
#include <core/gdt.h>

/*the global system_tss*/
tss_t system_tss;

static unsigned char kernel_stack[KSTACK_SIZE];
void *kstackend;

void tss_init() {
	DEBUG_MSG(("TSS descriptor: 0x%x", GDT_ENTRY_TSS * sizeof(struct gdt_descriptor)));

	//setup system tss
	system_tss.ldt = 0;
	system_tss.ss0 = 0x10;
	DEBUG_MSG(("Creating KSTACK %i", KSTACK_SIZE));
	system_tss.esp0 = kstackend = ((unsigned int) kernel_stack) + KSTACK_SIZE - 1000;
	//system_tss.cr3 = read_cr3();
	TRACE_MSG(("Created kstackend: %i", kstackend));
	
	DEBUG_MSG(("adding TSS to GDT"));
	gdt_set_gate(GDT_ENTRY_TSS, (unsigned int) &system_tss, sizeof(tss_t), 0x89, 0x0F);

	gdt_flush();

	DEBUG_MSG(("loading tss"));
	__asm__ volatile ("ltr %%ax" : : "a" (GDT_ENTRY_TSS * sizeof(struct gdt_descriptor)) );
	DEBUG_MSG(("loaded tss"));
}

