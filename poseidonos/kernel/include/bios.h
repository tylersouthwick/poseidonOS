/* File: bios.h
   Discription: Implements C wrappers for BIOS access*/
#ifndef BIOS_H
#define BIOS_H

#define outportb(port, value) asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value))
#define INPORTB(ret, port) asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port))

unsigned char inportb(int port);

#define crtc_io_adr 0x3D4

#endif
