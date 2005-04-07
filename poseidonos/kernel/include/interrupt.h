/* File: interrupt.h
   Discription: Implements interrupt setup and execution*/
#ifndef INTERRUPT_H
#define INTERRUPT_H
//assembly wrappers
void int_00();
void int_01();
void int_02();
void int_03();
void int_04();
void int_05();
void int_06();
void int_07();
void int_09();
void int_08();
void int_10();
void int_11();
void int_12();
void int_13();
void int_14();
void int_16();
void int_17();
void int_18();
void int_19();

//C functions
void isr00();
void isr01();
void isr02();
void isr03();
void isr04();
void isr05();
void isr06();
void isr07();
void isr08();
void isr09();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr16();
void isr17();
void isr18();
void isr19();

void user_interrupt_hook_asm();
#endif
