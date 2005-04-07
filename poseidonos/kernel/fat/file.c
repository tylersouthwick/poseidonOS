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

	fat_get_sector(fname, &sector_start, &sector_count, &isDirectory);


	if (!isDirectory && sector_start > 0)
	{
		char *read_buffer;
		int i;

		read_buffer = kmalloc(512);
		floppy_block_read(sector_start, read_buffer, 1);
		
		for (i=0; i<512; i++)
		{
			#ifdef FILE_PUTCHAR
			put_char(read_buffer[i]);
			put_char(32);
			#else
			put_int(read_buffer[i], 10);
			put_char(32);
			#endif
		}
	} else 
		kprint("ERROR! reading file\n");
	return (FILE *)0;
}

void fat_fclose(FILE *file)
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

