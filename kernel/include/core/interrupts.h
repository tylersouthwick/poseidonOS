#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#define INTERRUPT_COUNT 256

void interrupt0();
void isr0();

void keyboard_interrupt();
void keyboard_isr();

#endif
