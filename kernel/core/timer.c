#include <core/timer.h>
#include <kdebug.h>
#include <core/idt.h>

static int count = 0;

void timer_init() {
    DEBUG(("init pit"));
    idt_interrupt_add(0x20, timer_isr, 0);
    pit_init();
    DEBUG(("pit inited"));
}

void timer_interrupt() {
	count++;
	if (count == 1000) {
    		DEBUG(("timer"));
		count = 0;
	}
}