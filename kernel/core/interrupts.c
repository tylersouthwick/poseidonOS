#include <kdebug.h>

void interrupt0();
void keyboard_interrupt();

void interrupt0() {
    FATAL(("Attempted to divide by zero."));
    DEBUG(("Eventually, this should only kill the current task."));
    asm("hlt");
}

void keyboard_interrupt() {
    DEBUG(("keyboard!"));
}
