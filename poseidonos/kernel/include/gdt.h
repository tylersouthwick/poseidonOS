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

void gdt_init(void);

extern int gdt_kernel_code;
extern int gdt_kernel_data;
extern int gdt_user_code;
extern int gdt_user_data;
extern int gdt_tss;

extern struct gdt_descriptor GDT;

struct gdt_descriptor {
	unsigned short limit;
	unsigned short base015;
	unsigned char base1623;
	unsigned char access;
	unsigned char granularity;
	unsigned char base2431;
}__attribute__((packed));

static inline void gdt_add_descriptor(struct gdt_descriptor* gdt_entry, int base, int limit, char granularity, int sys_available, int present, int dpl, int system, int type) {
#ifdef DEBUG_GDT
	int operation_size = 1;
	KLOG_DEBUG("adding gdt_descriptor:\n\tbase: ");
	KLOG_INT_DEBUG(base, 0x10);
	KLOG_DEBUG("\n\tlimit: ");
	KLOG_INT_DEBUG(limit, 0x10);
	KLOG_DEBUG("\n\tgranularity: ");
	KLOG_INT_DEBUG(granularity, 10);
	KLOG_DEBUG("\n\toperation_size: ");
	KLOG_INT_DEBUG(operation_size, 10);
	KLOG_DEBUG("\n\tsys_available: ");
	KLOG_INT_DEBUG(sys_available, 10);
	KLOG_DEBUG("\n\tpresent: ");
	KLOG_INT_DEBUG(present, 10);
	KLOG_DEBUG("\n\tdpl: ");
	KLOG_INT_DEBUG(dpl, 10);
	KLOG_DEBUG("\n\tsystem: ");
	KLOG_INT_DEBUG(system, 10);
	KLOG_DEBUG("\n\ttype: ");
	KLOG_INT_DEBUG(type, 10);
	KLOG_DEBUG("\n");
#endif
}

int gdt_get_selector(int selector);

#endif
