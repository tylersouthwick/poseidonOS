#include <libc.h>
#include <kdebug.h>

void libc_isr();

void libc_init() {
	INFO_MSG(("Registering libc interrupt"));
	idt_interrupt_add(LIBC_INTERRUPT, libc_isr, 0);
	INFO_MSG(("Registered libc interrupt"));
}
