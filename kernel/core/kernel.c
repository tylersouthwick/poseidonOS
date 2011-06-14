#include <kdebug.h>
#include <screen.h>
#include <gdt.h>
#include <idt.h>
#include <string.h>

void kmain();

void kmain() {
    initScreen();
    clear_screen();
    INFO(("Booting PoseidonOS v1.0"));

    idt_setup();

    gdt_init();

    enable_ints();
    while(1);
}
