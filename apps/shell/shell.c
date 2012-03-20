#include <libc.h>

int _start() {
	libc_write_string("hello world!");
	return 0;
}

