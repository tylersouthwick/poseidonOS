/* File: interrupts.c
   Discription: Implements interrupt function calls*/

#include <screen.h>
#include <interrupt.h>
#include <mm.h>
#include <bios.h>
#include <paging.h>

#define MASTER 0x20
#define EOI 0x20

void panic()
{
	kprint("\nKernel Panic:\n");
	kprint("\teax: ");
	kprint("\tebx: ");
	kprint("\tecx: ");
	kprint("\tedx: ");
}

void int_00() {
	kprint("ERROR: Divide by Zero Error (#00)");
	asm("cli");
	panic();
	while(1);
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
	kprint("ERROR: Overflow (#OF)");
	outportb(MASTER,EOI);
}
void int_05() {
	kprint("ERROR: BOUND Range Exceeded (#BR)");
	outportb(MASTER,EOI);
}
void int_06() {
	kprint("ERROR: Invalid Opcode (#UD)");
	outportb(MASTER,EOI);
}
void int_07() {
	kprint("ERROR: Device Not Available (#NM)");
	outportb(MASTER,EOI);
}
void int_08() {
	kprint("ERROR: Double Fault (#DF)");
	outportb(MASTER,EOI);
}
void int_09() {
	kprint("ERROR: Coprocessor Segment Overrun");
	outportb(MASTER,EOI);
}
void int_10() {
	kprint("ERROR: Invalid TSS (#TS)");
	outportb(MASTER,EOI);
}
void int_11() {
	kprint("ERROR: Segment Not Present (#NP)");
	outportb(MASTER,EOI);
}
void int_12() {
	kprint("ERROR: Stack-Segment Fault (#SS)");
	outportb(MASTER,EOI);
}
void int_13() {
	kprint("ERROR: General Protection (#GP)");
	asm("cli");
	panic();
	while(1);
}

void int_14() {
	//do something about pagefault
	//..

	//print error if not successful return
	kprint("\nERROR: Page Fault (#PF) at: ");
	put_int((int)(read_cr2()),16);
	asm("cli");
	asm("hlt");
	while(1);
}
void int_16() {
	kprint("ERROR: x87 FPU Floating-Point Error (#MF)");
	outportb(MASTER,EOI);
}
void int_17() {
	kprint("ERROR: Alignment Check (#AC)");
	outportb(MASTER,EOI);
}
void int_18() {
	kprint("ERROR: Machine Check (#MC)");
	outportb(MASTER,EOI);
}
void int_19() {
	kprint("ERROR: SIMD Floating-Point Exception (#XF)");
	outportb(MASTER,EOI);
}
