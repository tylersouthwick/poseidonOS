/* File: bios.h
   Discription: Implements C wrappers for BIOS access*/
#ifndef BIOS_H
#define BIOS_H

//#define outportb(port, value) asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value))
//#define INPORTB(ret, port) asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port))

static inline void outportb(int port, int value)
{
	asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}

static inline unsigned char inportb(int port)
{
	int ret;
	asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
	return ret;
}

#define crtc_io_adr 0x3D4

#endif
