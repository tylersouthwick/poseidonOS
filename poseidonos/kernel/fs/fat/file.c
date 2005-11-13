#include <ktypes.h>
#include <kdebug.h>

#include <devices/floppy.h>
#include <kmalloc.h>

#include <fat.h>

#define FILE_PUTCHAR

/*this only supports reading right now*/
FILE *fat_fopen(struct vfs_mount *vmount, char *fname, char *mode)
{
	int sector_start;
	int sector_count;
	int isDirectory;
	vfs_entry *entry;
	FILE *file;

	fat_get_first_sector(vmount, fname, &sector_start, &sector_count, &isDirectory);

	file = (FILE *)kmalloc(sizeof(FILE));

	/* get size of file */
	entry = fat_ls(vmount, fname, &(file->size));
	file->size = entry->size;
	kfree(entry);

	file->data = kmalloc(file->size);
	file->offset = 0;

	if (!isDirectory && sector_start > 0)
	{
		char *read_buffer;

		read_buffer = file->data;

		do
		{
			floppy_block_read(sector_start, read_buffer, 1);
			read_buffer += 512;
		} while ((sector_start = fat_get_next_sector(vmount, sector_start)) != -1);

		return file;
	} 
		
	return (FILE *)NULL;
}

void fat_fclose(vfs_mount *vmount, FILE *file)
{
	kfree(file->data);
	kfree(file);
}

FILE *fat_file_create(vfs_mount *vmount, char *fname)
{
	FILE *file;

	/*create a new file here*/

	return file;
}

int fat_file_remove(vfs_mount *vmount, char *fname)
{
	/*remove file*/
	return -1;
}

int fat_file_write(vfs_mount *vmount, char *fname, char *data)
{
	/*write a file*/
	return -1;
}

int fat_file_read(vfs_mount *vmount, char *fname, char *data)
{
	/*read file*/
	return -1;
}

char fat_getchar(vfs_mount *vmount, FILE *file)
{
	if (file->size - file->offset == 0)
		return EOF;

	return file->data[file->offset++];
}


