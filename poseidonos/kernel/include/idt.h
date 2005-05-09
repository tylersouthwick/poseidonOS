/* File: idt.h
   Description: Defines IDT structure and control*/

#ifndef IDT_H
#define IDT_H

#define INT_0 0x8E00	//1000111000000000 = present, ring0, int_gate
#define INT_3 0xEE00  //1110111000000000 = present,ring3,int_gate

/* IDT structures */
typedef struct
{
	unsigned short low_offset;			//low nibble of offset to handler of interrupt
	unsigned short selector;			//GDT selector used
	unsigned short settings;			//settings for int
	unsigned short high_offset;			//high nibble to handle code
} __attribute__ ((packed)) x86_interrupt;

typedef struct
{
	unsigned short limit;				//size of IDT
	x86_interrupt *base;				//a pointer to IDT base
} __attribute__ ((packed)) idtr_t;
/**************************************************************************/

/*******************************Prototypes*********************************/
void idt_setup(void);
void idt_interrupt_add(int, void *, unsigned int);
void idt_user_setup(void);
/**************************************************************************/

#include <bios.h>

#define enable_ints() outportb(0x21, 0x00)

#endif
