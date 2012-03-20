#include <libc.h>
#include <kdebug.h>
#include <screen.h>

void libc_handler(int operation, void *data) {
	INFO_MSG(("Invoking libc handler!"));
	switch (operation) {
		case libc_write_string: {
			write_string((char *) data);
			break;
		}
		case libc_clear_screen: {
			clear_screen();
			break;
		}
		default: {
			ERROR_MSG(("Invalid operation: %i", operation));
		}
	}
}
