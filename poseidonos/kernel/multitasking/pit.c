#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <bios.h>

void pit_setup(int freq)
{
	int counter;

	counter = 0x1234dd / freq;

	outportb(0x43, 0x34);
	outportb(0x40, counter % 256);
	outportb(0x40, counter / 256);
}

