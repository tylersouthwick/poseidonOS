#include <kdebug.h>
#include <screen.h>

void kmain() {
    initScreen();
    clear_screen();
    INFO("Booting PoseidonOS v1.0\n");
    DEBUG("test");
    while(1);
}
