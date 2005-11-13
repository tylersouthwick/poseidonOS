/* File: gdt.h
   Discription: Implements C wrappers for gdt stuff*/

#ifndef GDT_H
#define GDT_H

#define DEBUG_GDT

#include <screen.h>
#include <string.h>

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

void gdt_init(void);

extern int gdt_kernel_code;
extern int gdt_kernel_data;
extern int gdt_user_code;
extern int gdt_user_data;
extern int gdt_tss;

extern struct gdt_descriptor GDT;

struct gdt_descriptor
{
	unsigned short limit;
	unsigned short base015;
	unsigned char base1623;
	unsigned char access;
	unsigned char granularity;
	unsigned char base2431;
}__attribute__((packed));

static inline void gdt_add_descriptor(struct gdt_descriptor* gdt_entry, int base, int limit, char granularity, int sys_available, int present, int dpl, int system, int type) {
	int operation_size = 1;
		#ifdef DEBUG_GDT
				kprint("adding gdt_descriptor:\n\tbase: ");
				put_int(base, 0x10);
				kprint("\n\tlimit: ");
				put_int(limit, 0x10);
				kprint("\n\tgranularity: ");
				put_int(granularity, 10);
				kprint("\n\toperation_size: ");
				put_int(operation_size, 10);
				kprint("\n\tsys_available: ");
				put_int(sys_available, 10);
				kprint("\n\tpresent: ");
				put_int(present, 10);
				kprint("\n\tdpl: ");
				put_int(dpl, 10);
				kprint("\n\tsystem: ");
				put_int(system, 10);
				kprint("\n\ttype: ");
				put_int(type, 10);
				kprint("\n");
#endif

}

#endif
