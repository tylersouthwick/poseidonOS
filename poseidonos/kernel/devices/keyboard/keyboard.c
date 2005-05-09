/***********************************************
 * keyboard.c
 * ********************************************/

#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <bios.h>
#include <irq.h>

#include <devices/manager.h>
#include <devices/keyboard.h>

extern void keyboard_isr(void);

void keyboard_init() {
	kprint("setting up keyboard....\n");

	idt_interrupt_add(0x21, keyboard_isr, 0);
	irq_umask(IRQ_1);
}

void keyboard_irq() {
				/*
	unsigned char al, ah;
	unsigned char raw_key;

	raw_key = inportb(0x60);
	al = inportb(0x61);
	al |= 0x82;
	outportb(0x61, al);
	al &= 0x7f;
	outportb(0x61, al);
	*/
	static unsigned char scancode;
	unsigned char status;

	status = inportb(0x64);
	scancode = inportb(0x60);
	kprint("key pressed...(scancode: ");
	put_int(scancode, 10);
	kprint(", status: ");
	put_int(status, 10);
	kprint (")\n");
}
