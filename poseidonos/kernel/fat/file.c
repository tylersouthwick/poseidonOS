#include <fat.h>
#include <vfs.h>
#include <screen.h>
#include <kmalloc.h>
#include <ktypes.h>

FILE *fat_fopen(char *fname, char *mode)
{
	int sector_start;
	int sector_count;
	int isDirectory;

	kprint("opening file ");
	kprint(fname);
	kprint(" (");
	kprint(mode);
	kprint(")\n");

	fat_get_sector(fname, &sector_start, &sector_count, &isDirectory);

	if (isDirectory)
		kprint("this is a directory\n");
	else
		kprint("this is not a directory\n");

	{
		char *read_buffer;
		int i;

		read_buffer = kmalloc(512);
		floppy_block_read(sector_start, read_buffer, 1);
		
		for (i=0; i<512; i++)
			put_char(read_buffer[i]);
	}
	return (FILE *)0;
}

void fat_fclose(FILE file)
{
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

