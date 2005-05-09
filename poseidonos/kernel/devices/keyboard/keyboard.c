/***********************************************
 * keyboard.c
 * ********************************************/

#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <bios.h>
#include <irq.h>

#include <devices/manager.h>
#include <devices/keyboard.h>

/************************************************************/
#define KEYBOARD_BUFFER_SIZE 1024

static unsigned char *keyboard_buffer;
static unsigned int keyboard_buffer_index;
static unsigned int is_done;
/************************************************************/

extern void keyboard_isr(void);

static char scancodes[] = KEYBOARD_QWERTY;

void keyboard_init() {
	idt_interrupt_add(0x21, keyboard_isr, 0);
	irq_umask(IRQ_1);

	/*initilize keyboard buffer*/
	keyboard_buffer = kmalloc(KEYBOARD_BUFFER_SIZE);
	keyboard_buffer_index = 0;
}

static char convert_scancode(int scancode)
{
	if (scancode >= sizeof(scancodes))
		return 0;
	return scancodes[scancode];
}

void keyboard_irq() {
	static unsigned char scancode;
	unsigned char status;
	char ch;

	status = inportb(0x64);
	scancode = inportb(0x60);
	ch = convert_scancode(scancode);
	if (ch)
	{
		put_char(ch);
		if (keyboard_buffer)
		{
			if (ch == '\b')
				keyboard_buffer_index--;
			else {
				keyboard_buffer[keyboard_buffer_index++] = ch;
				if (ch == KEY_ENTER)
					is_done = 1;
			}
		}
	}
}

void gets(char *buffer, int length)
{
	keyboard_buffer = kmalloc(KEYBOARD_BUFFER_SIZE);
	keyboard_buffer_index = 0;
	is_done = 0;

	while (!is_done);

	if (length < keyboard_buffer_index)
		keyboard_buffer_index = length;
	memcpy(buffer, keyboard_buffer, keyboard_buffer_index);
	kfree(keyboard_buffer);
}
