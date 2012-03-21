#include <libc.h>
#include <kdebug.h>
#include <screen.h>

void libc_handler(int operation, int data) {
	DEBUG_MSG(("Invoking libc handler: %i", operation));
	switch (operation) {
		case libc_write_character: {
			TRACE_MSG(("write character %c", data));
			write_char((char) data);
			break;
		}
		case libc_clear_screen: {
			TRACE_MSG(("clear screen"));
			clear_screen();
			break;
		}
		default: {
			ERROR_MSG(("Invalid operation: %i", operation));
		}
	}
	DEBUG_MSG(("Invoked libc handler: %i", operation));
}
