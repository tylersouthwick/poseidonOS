#include <ktypes.h>
#include <kdebug.h>

#include <fat.h>
#include <screen.h>
#include <string.h>
#include <kmalloc.h>

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
			
			KLOG_DEBUG (attributes);
			KLOG_DEBUG("  ");
			if (entries[i].size < 10)
				put_char(' ');
			if (entries[i].size < 100)
				put_char(' ');
			if (entries[i].size < 1000)
				put_char(' ');
			if (entries[i].size < 10000)
				put_char(' ');

			put_int(entries[i].size, 10);
			KLOG_DEBUG("  ");
			{
				struct kdate date;
				memcpy(&date, &entries[i].modified_date, sizeof(struct kdate));
				if (date.day < 10)
					put_char(' ');

				put_int(date.day, 10);
				put_char(' ');
				KLOG_DEBUG(months[date.month]);
				put_char(' ');
				put_int(date.year, 10);
			}
			KLOG_DEBUG("  ");
			KLOG_DEBUG(entries[i].name);
			KLOG_DEBUG("\n");
		}
	} else 
		KLOG_ERROR("invalid path!\n");

	return entries;
}

