#include <core/interrupts.h>
#include <core/idt.h>
#include <kdebug.h>
#include <bios.h>
#include <core/irq.h>
#include <string.h>

static idtr_t idtr;
static x86_interrupt IDT[INTERRUPT_COUNT];

void isr_empty();
void idt_setup() {
	int i;
    DEBUG_MSG(("Setting up IDT -> interrupts 0..%i", INTERRUPT_COUNT));
    idtr.limit = INTERRUPT_COUNT * (sizeof(x86_interrupt) - 1);
    idtr.base = IDT;

    memset(IDT, 0, sizeof(IDT));
    for (i = 0; i < INTERRUPT_COUNT; i++) {
	    idt_interrupt_add(i, isr_empty, 0);
    }
    idt_interrupt_add(0, isr0, 0);

    idtr_t *IDTRptr = &idtr;

    //remap programable interrupt controller PIC
    pics_init(0x20, 0x28);

    //load IDTR with lidt
    __asm__ volatile("LIDT (%0) ": :"p" (IDTRptr));
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
//    __asm__ volatile("movw %%cs,%0" :"=g"(selector));

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
    TRACE_MSG(("IDT[%i].low_offset = %i", number, IDT[number].low_offset));
    TRACE_MSG(("IDT[%i].selector = %i", number, IDT[number].selector));
    TRACE_MSG(("IDT[%i].settings = %i", number, IDT[number].settings));
    TRACE_MSG(("IDT[%i].high_offset = %i", number, IDT[number].high_offset));
}
