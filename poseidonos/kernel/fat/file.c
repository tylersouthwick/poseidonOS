#include <fat.h>
#include <vfs.h>
#include <screen.h>
#include <kmalloc.h>
#include <ktypes.h>

#define FILE_PUTCHAR

/*this only supports reading right now*/
FILE *fat_fopen(char *fname, char *mode)
{
	int sector_start;
	int sector_count;
	int isDirectory;
	vfs_entry *entry;
	FILE *file;

	fat_get_sector(fname, &sector_start, &sector_count, &isDirectory);

	file = (FILE *)kmalloc(sizeof(FILE));

	/* get size of file */
	entry = fat_ls(fname, &(file->size));
	file->size = entry->size;
	kfree(entry);

	if (file->size > 512)
		file->size = 512;

	file->data = kmalloc(file->size);
	file->offset = 0;

	if (!isDirectory && sector_start > 0)
	{
		char *read_buffer;
		int i;

		read_buffer = kmalloc(512);
		floppy_block_read(sector_start, read_buffer, 1);

		memcpy(file->data, read_buffer, file->size);

		return file;
	} 
		
	return (FILE *)NULL;
}

void fat_fclose(FILE *file)
{
	kfree(file->data);
	kfree(file);
}

FILE *fat_file_create(char *fname)
{
}

int fat_file_remove(char *fname)
{
}

int fat_file_write(char *fname, char *data)
{
}

int fat_file_read(char *fname, char *data)
{
}

char fat_getchar(FILE *file)
{
	if (file->size - file->offset == 0)
		return EOF;

	return file->data[file->offset++];
}


