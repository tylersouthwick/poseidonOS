/***********************************************
 * keyboard.c
 * ********************************************/

#include <ktypes.h>
#include <kdebug.h>

#include <bios.h>
#include <irq.h>
#include <screen.h>
#include <idt.h>
#include <string.h>
#include <kmalloc.h>

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
static char caps_scancodes[] = KEYBOARD_QWERTY_CAPS;

void keyboard_init() {
	idt_interrupt_add(0x21, keyboard_isr, 0);
	irq_umask(IRQ_1);

	/*initilize keyboard buffer*/
	keyboard_buffer = 0;
	keyboard_buffer_index = 0;
}

static bool is_shifted;
static bool is_capslocked;

static char convert_scancode(int scancode)
{
	char ch;

	if (scancode >= sizeof(scancodes))
		return 0;

	ch = scancodes[scancode];

	if (ch == KEY_SHIFT)
	{
		is_shifted = true;
		return 0;
	}

	if (ch == KEY_CAPSLOCK)
	{
		is_capslocked = (is_capslocked) ? false : true;

		return 0;
	}

	if (is_shifted || is_capslocked)
	{
		ch = caps_scancodes[scancode];
		is_shifted = false;
	}

	is_shifted = false;

	return ch;
}

void keyboard_irq() {
	static unsigned char scancode;
	unsigned char status;
	char ch;

	status = inportb(0x64);
	scancode = inportb(0x60);
	ch = convert_scancode(scancode);

	KDEBUG("status: ");
	KDEBUG_HEX(status);
	KDEBUG("\n");

	/*
	if (ch)
	{
		if (keyboard_buffer)
		{
			if (ch == '\b')
			{
				if (keyboard_buffer_index > 0)
				{
					keyboard_buffer_index--;
					put_char(ch);
				}
			}
			else {
				keyboard_buffer[keyboard_buffer_index++] = ch;
				put_char(ch);
				if (ch == KEY_ENTER)
					is_done = 1;
			}
		} else
			put_char(ch);
	}
	*/
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
	keyboard_buffer = 0;
}
