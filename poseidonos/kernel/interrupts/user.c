#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <interrupt.h>

void idt_user_setup()
{
	idt_interrupt_add(0x45, user_interrupt_hook_asm, 3);
}

void user_interrupt_hook()
{
	kprint("you called the user interrupt hook!\n");
}
