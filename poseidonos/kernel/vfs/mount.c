#include <ktypes.h>
#include <fat.h>
#include <mount.h>
#include <vfs.h>
#include <screen.h>
#include <kmalloc.h>
#include <string.h>

///this is assumed to be at fd0
void mount_root()
{
	vfs_entry *entries;

	fat_mount();
	kprint("mount done!\n");

	//entries = ls("/some/..");
	//if (entries != 0)
	//	kfree(entries);

//	kprint("\nListing done!\n");

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
}

