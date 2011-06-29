#include <multitasking/timer.h>
#include <kdebug.h>
#include <core/idt.h>

void timer_init() {
    DEBUG(("Initializing PIT"));
    idt_interrupt_add(0x20, timer_isr, 0);
    struct PIT_RETURN *pitReturn = pit_init(200);
    DEBUG(("PIT initialized %iHz every %i.%ims", pitReturn->irq0_frequency, pitReturn->irq0_ms, pitReturn->irq0_fractions));
}

