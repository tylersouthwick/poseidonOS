#include <ktypes.h>
#include <kdebug.h>
#include <screen.h>
#include <idt.h>
#include <interrupt.h>
#include <devices/keyboard.h>

void idt_user_setup()
{
  kprint("adding user_interrupt_hook_asm2");
	idt_interrupt_add(0x45, user_interrupt_hook_asm2, 0);
	//idt_interrupt_add(0x46, user_interrupt_hook_asm2, 3);
}

void user_interrupt_hook(char test) {
	put_char(test);
}

void user_interrupt_hook2() {
	//char *buffer;
	kprint("getting string...\n");

  /*
	buffer = (char *)kmalloc(512);
	gets(buffer, 512);
	kprint("done: ");
	kprint(buffer);
	kprint("\n");
  */
}
