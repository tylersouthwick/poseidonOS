/* File: gdt.h
   Discription: Implements C wrappers for gdt stuff*/

#ifndef GDT_H
#define GDT_H

#include <screen.h>

#define GDT_TYPE_DATA_RO 0
#define GDT_TYPE_DATA_RO_ACCESSED 1
#define GDT_TYPE_DATA_RW 2
#define GDT_TYPE_DATA_RW_ACCESSED 3
#define GDT_TYPE_DATA_RO_EXPAND_DOWN 4
#define GDT_TYPE_DATA_RO_EXPAND_DOWN_ACCESSED 5
#define GDT_TYPE_DATA_RW_EXPAND_DOWN 6
#define GDT_TYPE_DATA_RW_EXPAND_DOWN_ACCESSED 7

#define GDT_TYPE_CODE_EXECUTE_ONLY 8
#define GDT_TYPE_CODE_EXECUTE_ONLY_ACCESSED 9
#define GDT_TYPE_CODE_EXECUTE_READ 10
#define GDT_TYPE_CODE_EXECUTE_READ_ACCESSED 11
#define GDT_TYPE_CODE_EXECUTE_ONLY_CONFORMING 12
#define GDT_TYPE_CODE_EXECUTE_ONLY_CONFORMING_ACCESSED 13
#define GDT_TYPE_CODE_EXECUTE_ONLY_READ_ONLY_CONFORMING 14
#define GDT_TYPE_CODE_EXECUTE_READ_ONLY_CONFORMING_ACCESSED 15

#define GDT_ENTRY_COUNT 32

#define GDT_ENTRY_NULL 0
#define GDT_ENTRY_KERNEL_CODE 1
#define GDT_ENTRY_KERNEL_DATA 2
#define GDT_ENTRY_USERSPACE_CODE 3
#define GDT_ENTRY_USERSPACE_DATA 4
#define GDT_ENTRY_TSS 5

struct gdt_descriptor {
	unsigned short limit;
	unsigned short base_lo;
	unsigned char base_mid;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_hi;
}__attribute__((packed));

struct gdt_table {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

void gdt_set_gate(unsigned int num, unsigned int base, unsigned int limit, char access, unsigned int gran);
void gdt_init();

void gdt_load(struct gdt_table *);
void gdt_flush();

#endif
