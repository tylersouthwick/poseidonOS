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
static char *keyboard_buffer;
/************************************************************/

extern void keyboard_isr(void);

static char scancodes[] = {0, 
				KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, 
				KEY_HYPHEN, KEY_EQUALS, KEY_BACKSPACE, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, 
				KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_OPEN_SQUARE_BRACKET, 
				KEY_CLOSE_SQUARE_BRACKET, KEY_ENTER, KEY_LEFT_CONTROL, KEY_A, KEY_S, KEY_D, KEY_F, 
				KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMI_COLEN, KEY_APOSTOPHE, KEY_TICK, 
				KEY_LEFT_SHIFT, 0, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, 
				KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT, KEY_KEYPAD_ASTRISK, KEY_LEFT_ALT, KEY_SPACEBAR, 
				KEY_CAPSLOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, 
				KEY_F10, KEY_KEYPAD_NUMLOCK, KEY_SCROLL_LOCK, KEY_KEYPAD_7, KEY_KEYPAP_8, KEY_KEYPAD_9, 
				KEY_KEYPAD_HYPHEN, KEY_KEYPAD_4, KEY_KEYPAD_5, KEY_KEYPAD_6, KEY_KEYPAD_PLUS, KEY_KEYPAD_1, 
				KEY_KEYPAD_2, KEY_KEYPAD_3, KEY_KEYPAD_0, KEY_KEYPAD_PERIOD, 0, 0, 0, KEY_F11, KEY_F12
};

void keyboard_init() {
	idt_interrupt_add(0x21, keyboard_isr, 0);
	irq_umask(IRQ_1);

	/*initilize keyboard buffer*/
	keyboard_buffer = kmalloc(KEYBOARD_BUFFER_SIZE);

	kprint("scancodes => ");
	put_int(sizeof(scancodes), 10);
	kprint("\n");
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
		put_char(ch);
}
