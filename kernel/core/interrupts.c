#include <kdebug.h>

void interrupt0();
void keyboard_interrupt();
void empty_interrupt();

void interrupt0() {
    FATAL_MSG(("Attempted to divide by zero."));
    DEBUG_MSG(("Eventually, this should only kill the current task."));
    __asm__("hlt");
}

void keyboard_interrupt() {
    DEBUG_MSG(("keyboard!"));
}

void empty_interrupt() {
	DEBUG_MSG(("empty interrupt"));
}
