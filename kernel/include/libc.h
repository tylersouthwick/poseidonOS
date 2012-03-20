#ifndef LIBC_H
#define LIBC_H

#define LIBC_INTERRUPT 0x80

void libc_init();

//operations
enum LibC_Opts {
	libc_clear_screen,
	libc_write_string
};

#endif
