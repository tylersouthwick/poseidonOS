/* File: idt.c
   Description: Implements Interrupt Descriptor Table access*/

#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <idt.h>
#include <interrupt.h>
#include <irq.h>
#include <bios.h>

static idtr_t idtr;
static x86_interrupt IDT[256];

void idt_setup()
{
	idtr.limit = 256*(sizeof(x86_interrupt)-1);
	idtr.base = IDT;

	idt_interrupt_add(0, isr00, 0);
	idt_interrupt_add(1, isr01, 0);
	idt_interrupt_add(2, isr02, 0);
	idt_interrupt_add(3, isr03, 0);
	idt_interrupt_add(4, isr04, 0);
	idt_interrupt_add(5, isr05, 0);
	idt_interrupt_add(6, isr06, 0);
	idt_interrupt_add(7, isr07, 0);
	idt_interrupt_add(8, isr08, 0);
	idt_interrupt_add(9, isr09, 0);
	idt_interrupt_add(10, isr10, 0);
	idt_interrupt_add(11, isr11, 0);
	idt_interrupt_add(12, isr12, 0);
	idt_interrupt_add(13, isr13, 0);
	idt_interrupt_add(14, isr14, 0);
	idt_interrupt_add(16, isr16, 0);
	idt_interrupt_add(17, isr17, 0);
	idt_interrupt_add(18, isr18, 0);
	idt_interrupt_add(19, isr19, 0);
	idt_interrupt_add(20, 0, 0);
	idt_interrupt_add(21, 0, 0);
	idt_interrupt_add(22, 0, 0);
	idt_interrupt_add(23, 0, 0);
	idt_interrupt_add(24, 0, 0);
	idt_interrupt_add(25, 0, 0);
	idt_interrupt_add(26, 0, 0);
	idt_interrupt_add(27, 0, 0);
	idt_interrupt_add(28, 0, 0);
	idt_interrupt_add(29, 0, 0);
	idt_interrupt_add(30, 0, 0);
	idt_interrupt_add(31, 0, 0);

	//idt_interrupt_add(0x20, timer_isr, 0);
	idtr_t *IDTRptr = &idtr;

	//remap programable interrupt controller (PIC)
	pics_init(0x20, 0x28);
	//load IDTR with lidt
	asm volatile("LIDT (%0) ": :"p" (IDTRptr));
}

void pics_init(int pic1, int pic2)
{
	outportb(PIC1, ICW1);
	outportb(PIC2, ICW1);

	outportb(PIC1 + 1, pic1);
	outportb(PIC2 + 1, pic2);

	outportb(PIC1 + 1, 4);
	outportb(PIC2 + 1, 2);

	outportb(PIC1 + 1, ICW4);
	outportb(PIC2 + 1, ICW4);

	/*disable all irqs*/
	outportb(PIC1 + 1, 0xFF);
}

void idt_interrupt_add(int number, void (*handler)(), unsigned int dpl)
{
	unsigned short selector = 0x08;
	unsigned short settings = 0;
	unsigned int offset = (unsigned int) handler;

	//get CS selector
	asm volatile("movw %%cs,%0" :"=g"(selector));

	//set settings based on dpl
	switch(dpl)
	{
		case 0: settings = INT_0; break;
		case 1:
		case 2:
		case 3: settings = INT_3; break;
	}

	//set actual values of int
	IDT[number].low_offset	= (offset & 0xFFFF);
	IDT[number].selector	= selector;
	IDT[number].settings	= settings;
	IDT[number].high_offset	= (offset >> 16);
}
