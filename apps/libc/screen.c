#include "libc.h"
#include "libc_generated.h"

void clear_screen() {
	libc_clear_screen(0);
}

//this is really inefficient but we don't have to worry about copying memory to the kernel
//it works for now
void print(const char *str) {
	int i = 0;
	while (str[i] != 0) {
		char c = str[i++];
		libc_write_character((void *) c);
	}
}
