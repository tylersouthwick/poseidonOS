/* File: interrupts.c
   Discription: Implements interrupt function calls*/

#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <interrupt.h>
#include <paging.h>

#define MASTER 0x20
#define EOI 0x20

void kpanic(char *error_message)
{
	asm("cli");

	screen_set_color(SCREEN_BG_BLUE | SCREEN_FG_BRIGHT_WHITE);
	screen_clear();

	kprint("PoseidonOS v");
	put_int(POSEIDONOS_VERSION_MAJOR, 10);
	kprint(".");
	put_int(POSEIDONOS_VERSION_MINOR, 10);
	kprint(POSEIDONOS_VERSION_TYPE);
	kprint(" Kernel Panic:\n");

	kprint("\nWhat does this mean?\n");
	kprint("\tThere has been a fatal crash in the core of the system (called the kernel).  If you feel so inclined, then you can take note of the stack and register dump and attempt to fix the problem yourself.  Or else, please go to http://poseidonos.sf.net and report the bug.  Thanks!\n");

	kprint("\nError Message: ");
	kprint(error_message);

	kprint("\n\nStack dump: \n");

	kprint("\nRegister dump:\n");
	kprint("\teax: ");
	kprint("\tebx: ");
	kprint("\tecx: ");
	kprint("\tedx: ");
	asm("hlt");
	while(1);
}

void int_00() {
	kpanic("Divide by Zero Error (#00)");
}
void int_01() {
	kprint("ERROR: Debug Exception (#DB)");
	outportb(MASTER,EOI);
}
void int_02() {
	kprint("ERROR: NMI Exception");
	outportb(MASTER,EOI);
}
void int_03() {
	kprint("ERROR: Breakpoint (#BP)");
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
	kprint("\nERROR: Page Fault (#PF) at: ");
	put_int((int)(read_cr2()),16);
	kpanic("Page Fault (#PF) at:");
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
