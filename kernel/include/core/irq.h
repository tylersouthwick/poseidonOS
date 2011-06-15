#ifndef IRQ_H
#define IRQ_H

/******************IRQ Numbers***************************/
#define IRQ_0		1
#define IRQ_1		2
#define IRQ_2		4	
#define IRQ_3		8
#define IRQ_4		16
#define IRQ_5		32
#define IRQ_6		64
#define IRQ_7		128
/****************end IRQ Numbers*************************/

/*********************Control Codes**********************/
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01
/*******************end Control Codes********************/

extern unsigned int irq_mask;

static inline void irq_mask_all(void)
{
	asm volatile ("cli"); 
	irq_mask = 0; 
	asm volatile ("outb %%al,%%dx": :"d" (0x21), "a" (~(0xFF & irq_mask))); 
	asm volatile ("sti");
}

static inline void irq_umask(int a)
{
	asm volatile ("cli"); 
	irq_mask |= a; 
	asm volatile ("outb %%al,%%dx": :"d" (0x21), "a" (~(0xFF & irq_mask))); 
	asm volatile ("sti");
}

void pics_init(int, int);

#endif
