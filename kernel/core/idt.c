#include <core/interrupts.h>
#include <core/idt.h>
#include <kdebug.h>
#include <bios.h>
#include <core/irq.h>
#include <string.h>

static idtr_t idtr;
static x86_interrupt IDT[INTERRUPT_COUNT];

void idt_setup() {
    DEBUG(("Setting up IDT"));
    idtr.limit = INTERRUPT_COUNT * (sizeof(x86_interrupt) - 1);
    idtr.base = IDT;

    memset(IDT, 0, sizeof(IDT));
    idt_interrupt_add(0, isr0, 0);

    idtr_t *IDTRptr = &idtr;

    //remap programable interrupt controller PIC
    pics_init(0x20, 0x28);

    //load IDTR with lidt
    asm volatile("LIDT (%0) ": :"p" (IDTRptr));
}

void pics_init(int pic1, int pic2) {
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

void idt_interrupt_add(int number, void *handler, unsigned int dpl) {
    unsigned short selector = 0x08;
    unsigned short settings = 0;
    unsigned int offset = (unsigned int) handler;

    //get CS selector
    asm volatile("movw %%cs,%0" :"=g"(selector));

    //set settings based on dpl
    switch (dpl) {
        case 0:
            settings = INT_0;
            break;
        case 1:
        case 2:
        case 3:
            settings = INT_3;
            break;
    }

    //set actual values int
    IDT[number].low_offset = (offset & 0xFFFF);
    IDT[number].selector = selector;
    IDT[number].settings = settings;
    IDT[number].high_offset = (offset >> 16);
}
