#include <ktypes.h>
#include <fat.h>
#include <mount.h>
#include <vfs.h>
#include <screen.h>
#include <kmalloc.h>
#include <string.h>

void ls(char *path)
{
	vfs_entry *entries;
	vfs_entry *temp;
	int entries_count;
	int i;
	
	kprint("getting listing...");
	entries = fat_ls(path, &entries_count);
	kprint("okay!\n");

	if (entries > 0)
	{
		for (i=0; i < entries_count; i++)
		{
			if (VFS_IS_DIRECTORY(entries[i].attributes))
				kprint("<DIR> ");
			else
				kprint("      ");
			
			kprint(entries[i].name);
			kprint("\t");
			{
				struct kdate date;
				memcpy(&date, &entries[i].modified_date, sizeof(struct kdate));
				put_int(date.day, 10);
				put_char(' ');
				put_int(date.month, 10);
				put_char(' ');
				put_int(date.year, 10);
			}
			kprint("\n");
		}
	}
	return entries;
}

