#include <ktypes.h>
#include <fat.h>
#include <mount.h>
#include <vfs.h>
#include <screen.h>
#include <kmalloc.h>
#include <string.h>

char *months[] = {
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec"
};

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
			char attributes[5];

			if (VFS_IS_DIRECTORY(entries[i].attributes))
				attributes[0] = 'd';
			else
				attributes[0] = '-';

			if (VFS_IS_READ_ONLY(entries[i].attributes))
				attributes[1] = 'r';
			else
				attributes[1] = '-';

			if (VFS_IS_SYSTEM(entries[i].attributes))
				attributes[2] = 's';
			else
				attributes[2] = '-';

			if (VFS_IS_ARCHIVE(entries[i].attributes))
				attributes[3] = 'a';
			else
				attributes[3] = '-';

			attributes[4] = 0;
			
			kprint (attributes);
			kprint("  ");
			if (entries[i].size < 10)
				put_char(' ');
			if (entries[i].size < 100)
				put_char(' ');
			if (entries[i].size < 1000)
				put_char(' ');
			if (entries[i].size < 10000)
				put_char(' ');

			put_int(entries[i].size, 10);
			kprint("  ");
			{
				struct kdate date;
				memcpy(&date, &entries[i].modified_date, sizeof(struct kdate));
				if (date.day < 10)
					put_char(' ');

				put_int(date.day, 10);
				put_char(' ');
				kprint(months[date.month]);
				put_char(' ');
				put_int(date.year, 10);
			}
			kprint("  ");
			kprint(entries[i].name);
			kprint("\n");
		}
	} else 
		kprint("invalid path!\n");

	return entries;
}
