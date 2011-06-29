#include <kdebug.h>
#include <screen.h>
#include <core/gdt.h>
#include <core/idt.h>
#include <version.h>
#include <string.h>
#include <multitasking/multitasking.h>
#include <multiboot.h>
#include <mm/mm.h>

void kmain(multiboot_info_t *mm_info);

void kmain(multiboot_info_t *mm_info) {
    initScreen();
    clear_screen();
    INFO(("Booting PoseidonOS v%s", KERNEL_VERSION));

    idt_setup();

    gdt_init();

    mm_init(mm_info);

    multitasking_init();

    FATAL(("shouldn't get here!"));

    while(1);
}

void kernel_init() {
	DEBUG(("Entered multitasking environment"));
	INFO(("Initializing Kernel Subsystems"));

	while(1);
}
