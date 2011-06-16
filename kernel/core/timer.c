#include <core/timer.h>
#include <kdebug.h>
#include <core/idt.h>

void timer_init() {
    DEBUG(("Initializing PIT"));
    idt_interrupt_add(0x20, timer_isr, 0);
    struct PIT_RETURN *pitReturn = pit_init(1);
    DEBUG(("PIT initialized %iHz every %i.%ims", pitReturn->irq0_frequency, pitReturn->irq0_ms, pitReturn->irq0_fractions));
}

static int lastSecond = 0;
void timer_interrupt(long system_timer_ms) {
	int second = system_timer_ms / 1000;
	if (second > lastSecond) {
    		DEBUG(("timer: %is (%ims)", second, system_timer_ms));
		lastSecond = second;
	}
}
