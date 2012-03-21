#include <libc.h>
#define TRACE
#include <kdebug.h>
#include <screen.h>

void libc_handler(int operation, void *data) {
	DEBUG_MSG(("Invoking libc handler: %i", operation));
	switch (operation) {
		case libc_write_string: {
			TRACE_MSG(("write string @0x%x", data));
			write_string((char *) data);
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
