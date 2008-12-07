#include <ktypes.h>
#include <screen.h>
#include <gdt.h>
#include <multitasking.h>
#include <kdebug.h>
#include <memory.h>

static struct gdt_table gdt_table;

static struct gdt_descriptor gdt[GDT_ENTRY_COUNT];

void gdt_init() {
  gdt_table.limit = (sizeof(struct gdt_descriptor) * GDT_ENTRY_COUNT) -1;
  gdt_table.base = (unsigned int)&gdt;

  memset(gdt, 0, sizeof( struct gdt_descriptor) * GDT_ENTRY_COUNT);

  gdt_set_gate(GDT_ENTRY_NULL, 0, 0, 0, 0);
  gdt_set_gate(GDT_ENTRY_KERNEL_CODE, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_gate(GDT_ENTRY_KERNEL_DATA, 0, 0xFFFFFFFF, 0x92, 0xCF);
  gdt_set_gate(GDT_ENTRY_USERSPACE_CODE, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  gdt_set_gate(GDT_ENTRY_USERSPACE_DATA, 0, 0xFFFFFFFF, 0xF2, 0xCF);
}

void gdt_set_gate(unsigned int num, unsigned int base, unsigned int limit, char access, unsigned int gran) {
  if (num >= GDT_ENTRY_COUNT) {
    return;
  }

  gdt[num].base_lo = base &0xFFFF;
  gdt[num].base_mid = (base >> 16) & 0xFF;
  gdt[num].base_hi = (base >> 24) & 0xFF;

  gdt[num].limit = limit & 0xFFFF;
  gdt[num].granularity = (limit >> 16) & 0x0f;

  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void gdt_flush() {
  gdt_load(&gdt_table);
}
