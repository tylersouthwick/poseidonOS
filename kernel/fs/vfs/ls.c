#include <ktypes.h>
#include <kdebug.h>

#include <fat.h>
#include <screen.h>
#include <string.h>
#include <kmalloc.h>

static char *months[] = {
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

vfs_entry *ls(char *path)
{
	vfs_entry *entries;
	int entries_count;
	int i;
	vfs_mount *vmount;
	
	entries = fat_ls(vmount, path, &entries_count);

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
			
			char date_s[25];
			memset(date_s, 0, sizeof(date_s));
			struct kdate date;
			memcpy(&date, &entries[i].modified_date, sizeof(struct kdate));

			INFO(("%s %i [%i %s %i] -> %s", attributes, entries[i].size, date.day, months[date.month], date.year, entries[i].name));
		}
	} else {
		ERROR(("invalid path!"));
	}

	return entries;
}

