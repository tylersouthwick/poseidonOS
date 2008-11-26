/* File: interrupts.c
   Discription: Implements interrupt function calls*/

#include <ktypes.h>
#include <kdebug.h>
#include <screen.h>

#include <interrupt.h>
#include <bios.h>
#include <irq.h>

#include <mm/paging.h>

#define MASTER 0x20
#define EOI 0x20
void kpanic(char *);

void kpanic(char *error_message)
{
	asm volatile ("cli");
	KLOG_DEBUG("error message: ");
	KLOG_DEBUG(error_message);
/*
	screen_set_color(SCREEN_BG_BLUE | SCREEN_FG_BRIGHT_WHITE);
	screen_clear();

	KLOG_DEBUG("PoseidonOS v");
	put_int(POSEIDONOS_VERSION_MAJOR, 10);
	KLOG_DEBUG(".");
	put_int(POSEIDONOS_VERSION_MINOR, 10);
	KLOG_DEBUG(POSEIDONOS_VERSION_TYPE);
	KLOG_DEBUG(" Kernel Panic:\n");

	KLOG_DEBUG("\nWhat does this mean?\n");
	KLOG_DEBUG("\tThere has been a fatal crash in the core of the system (called the kernel).  If you feel so inclined, then you can take note of the stack and register dump and attempt to fix the problem yourself.  Or else, please go to http://poseidonos.sf.net and report the bug.  Thanks!\n");

	KLOG_DEBUG("\nError Message: ");
	KLOG_DEBUG(error_message);

	KLOG_DEBUG("\n\nStack dump: \n");

	KLOG_DEBUG("\nRegister dump:\n");
	KLOG_DEBUG("\teax: ");
	put_int(stack_poke(0x10), 0x10);
	KLOG_DEBUG("\tebx: ");
	KLOG_DEBUG("\tecx: ");
	KLOG_DEBUG("\tedx: ");
	KLOG_DEBUG("\nControl Registers:\n");
	KLOG_DEBUG("\tCR0: ");
	put_int(read_cr0(), 0x10);
	KLOG_DEBUG("\tCR2: ");
	put_int(read_cr2(), 0x10);
	KLOG_DEBUG("\tCR3: ");
	put_int(read_cr3(), 0x10);
	*/
	/*
	{
		int i;
		for (i=0; i<20; i++)
		{
			KLOG_DEBUG("\t");
			put_int(i, 10);
			KLOG_DEBUG(": ");
			put_int(stack_poke(-i), 0x10);
		}
	}
	*/
	asm volatile("hlt");
	irq_mask_all();
	while(1);
}

void int_00() {
	kpanic("Divide by Zero Error (#00)");
}
void int_01() {
	KLOG_DEBUG("ERROR: Debug Exception (#DB)");
	outportb(MASTER,EOI);
}
void int_02() {
	KLOG_DEBUG("ERROR: NMI Exception");
	outportb(MASTER,EOI);
}
void int_03() {
	KLOG_DEBUG("ERROR: Breakpoint (#BP)");
	outportb(MASTER,EOI);
}
void int_04() {
	kpanic("ERROR: Overflow (#OF)");
}
void int_05() {
	kpanic("BOUND Range Exceeded (#BR)");
}
void int_06() {
	kpanic("Invalid Opcode (#UD)");
}
void int_07() {
	kpanic("Device Not Available (#NM)");
}
void int_08() {
	kpanic("Double Fault (#DF)");
}
void int_09() {
	kpanic("Coprocessor Segment Overrun");
}
void int_10() {
	kpanic("Invalid TSS (#TS)");
}
void int_11() {
	kpanic("Segment Not Present (#NP)");
}
void int_12() {
	kpanic("Stack-Segment Fault (#SS)");
}
void int_13() {
	kpanic("General Protection (#GP)");
}

void int_14() {
	//do something about pagefault
	//..

	//print error if not successful return
	KLOG_DEBUG("page fault at ");
	put_int(read_cr2(), 0x10);
	KLOG_DEBUG("\n");

	kpanic("Page Fault (#PF)");
}
void int_16() {
	kpanic("x87 FPU Floating-Point Error (#MF)");
}
void int_17() {
	kpanic("Alignment Check (#AC)");
}
void int_18() {
	kpanic("Machine Check (#MC)");
}
void int_19() {
	kpanic("SIMD Floating-Point Exception (#XF)");
}
