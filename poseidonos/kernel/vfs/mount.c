#include <kernel.h>
#include <ktypes.h>
#include <kutil.h>
#include <kdebug.h>

#include <fat.h>

///this is assumed to be at fd0
int mount(char *dev, char *path)
{
	vfs_entry *entries;

	return fat_mount();

	/*
	entries = ls("/");
	if (entries != 0)
		kfree(entries);

	kprint("\nListing done!\n");
	*/

	/*
	{
		FILE f;

		f = fat_fopen("/boot/grub/menu.lst", "rw");
		//f = fat_fopen("/hello.msg", "rw");

		if (f > -1)
		{
			fat_fclose(f);
		} else {
			kprint("file not found!\n");
		}
	}
	*/
}

void umount_all()
{
}


