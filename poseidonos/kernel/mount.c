#include <ktypes.h>
#include <fat.h>
#include <mount.h>
#include <vfs.h>
#include <screen.h>
#include <kmalloc.h>

///this is assumed to be at fd0
void mount_root()
{
	fat_mount();
	kprint("mount done!\n");
	
	//fat_open("/hello.msg");
	
	{
		vfs_entry *entries;
		vfs_entry *temp;
		int entries_count;
		int i;
		
		kprint("getting listing...");
		entries = fat_ls("", &entries_count);
		kprint("okay!\n");
	
		for (i=0; i < entries_count; i++)
		{
			if (VFS_IS_DIRECTORY(entries[i].attributes))
				kprint("<DIR> ");
			else
				kprint("      ");
			
			kprint(entries[i].name);
			kprint("\n");
		}
		
		kfree(entries);
	}
}


