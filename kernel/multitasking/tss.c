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
#include <gdt.h>

/*the global system_tss*/
static tss_t system_tss;

static unsigned char kernel_stack[KSTACK_SIZE];

void tss_init() {
	KDEBUG("TSS descriptor: ");
	KDEBUG_HEX(GDT_ENTRY_TSS * sizeof(struct gdt_descriptor));
	KDEBUG("\n");

	//setup system tss
  system_tss.ldt = 0;
  system_tss.ss0 = 0x10;
	system_tss.esp0 = ((unsigned int) kernel_stack) + KSTACK_SIZE;
	//system_tss.cr3 = read_cr3();
  
  KDEBUG("adding TSS to GDT\n");
  gdt_set_gate(GDT_ENTRY_TSS, (unsigned int) &system_tss, sizeof(tss_t), 0x89, 0x0F);

  gdt_flush();

  KDEBUG("loading tss\n");
 
  asm volatile ("ltr %%ax" : : "a" (GDT_ENTRY_TSS * sizeof(struct gdt_descriptor)) );
}

