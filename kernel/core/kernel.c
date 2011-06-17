#include <kdebug.h>
#include <screen.h>
#include <core/gdt.h>
#include <core/idt.h>
#include <version.h>
#include <string.h>
#include <core/timer.h>

void kmain();

void kmain() {
    initScreen();
    clear_screen();
    INFO(("Booting PoseidonOS v%s", KERNEL_VERSION));

    kprintf("test: %llx", 0xABCDEFFEDCBA);
    idt_setup();

    gdt_init();

//    timer_init();

    enable_ints();

    while(1);
}
