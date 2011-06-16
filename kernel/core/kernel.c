#include <kdebug.h>
#include <screen.h>
#include <core/gdt.h>
#include <core/idt.h>
#include <version.h>
#include <string.h>
#include <core/timer.h>
#include <mm/mm.h>

void kmain();

void kmain(multiboot_info *mbt, unsigned int magic) {
    initScreen();
    clear_screen();
    INFO(("Booting PoseidonOS v%s", KERNEL_VERSION));

    idt_setup();

    gdt_init();

    mm_init();

//    timer_init();

    enable_ints();

    while(1);
}
