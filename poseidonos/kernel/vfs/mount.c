#include <kernel.h>
#include <ktypes.h>
#include <kutil.h>
#include <kdebug.h>

#include <fat.h>

///this is assumed to be at fd0
int mount(char *dev, char *path)
{
	return fat_mount();
}

void umount_all()
{
}


