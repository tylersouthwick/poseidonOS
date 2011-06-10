#include <kdebug.h>
#include <screen.h>
#include <gdt.h>
#include <idt.h>
#include <version.h>

void kmain() {
    initScreen();
    clear_screen();
    INFO(("Booting PoseidonOS v%s", KERNEL_VERSION));

    idt_setup();

    gdt_init();

    enable_ints();

    while(1);
}
