#include <bios.h>

///there wasn't a better place to put this, so it went into kernel.c
unsigned char inportb(int port)
{
	unsigned char temp;
	INPORTB(temp, port);
	return temp;
}
