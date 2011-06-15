#ifndef _CORE_TIMER_H
#define _CORE_TIMER_H

void pit_init();
void timer_init();
void timer_interrupt();
void timer_isr();

#endif
