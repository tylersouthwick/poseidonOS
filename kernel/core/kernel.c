#include <kdebug.h>
#include <screen.h>
#include <core/gdt.h>
#include <core/idt.h>
#include <version.h>
#include <string.h>
#include <core/timer.h>
#include <multiboot.h>
#include <mm/mm.h>

void kmain(multiboot_info_t *mm_info);

void kmain(multiboot_info_t *mm_info) {
    initScreen();
    clear_screen();
    INFO(("Booting PoseidonOS v%s", KERNEL_VERSION));

    idt_setup();

    mm_init(mm_info);

    gdt_init();

//    timer_init();

    enable_ints();

    while(1);
}
