#include <drivers.h>
#include <screen.h>
#include <floppy.h>

void drivers_load()
{
	kprint("load drivers...\n");
	floppy_init();
}
