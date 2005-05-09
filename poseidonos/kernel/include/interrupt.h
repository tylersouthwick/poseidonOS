/* File: interrupt.h
   Discription: Implements interrupt setup and execution*/
#ifndef INTERRUPT_H
#define INTERRUPT_H
//assembly wrappers
void int_00(void);
void int_01(void);
void int_02(void);
void int_03(void);
void int_04(void);
void int_05(void);
void int_06(void);
void int_07(void);
void int_09(void);
void int_08(void);
void int_10(void);
void int_11(void);
void int_12(void);
void int_13(void);
void int_14(void);
void int_16(void);
void int_17(void);
void int_18(void);
void int_19(void);

//C functions
void isr00(void);
void isr01(void);
void isr02(void);
void isr03(void);
void isr04(void);
void isr05(void);
void isr06(void);
void isr07(void);
void isr08(void);
void isr09(void);
void isr10(void);
void isr11(void);
void isr12(void);
void isr13(void);
void isr14(void);
void isr16(void);
void isr17(void);
void isr18(void);
void isr19(void);

void user_interrupt_hook_asm(void);
void user_interrupt_hook(char);

#endif
