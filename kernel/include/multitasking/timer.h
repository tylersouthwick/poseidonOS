#ifndef _CORE_TIMER_H
#define _CORE_TIMER_H

struct PIT_RETURN {
	int irq0_fractions;
	int irq0_ms;
	int irq0_frequency;
	int reload_value;
};

struct PIT_RETURN *pit_init(int hz);
void timer_init();
void timer_interrupt();
void timer_isr();

#endif
