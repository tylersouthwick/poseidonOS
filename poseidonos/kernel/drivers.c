#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <drivers.h>
#include <screen.h>

#include <devices/floppy.h>

int drivers_load()
{
				/*
	screen_set_color(SCREEN_FG_CYAN | SCREEN_BG_BLACK);
	kprint("floppy ");
	screen_set_color(SCREEN_DEFAULT);
	floppy_init();
	*/
				return 0;
}
