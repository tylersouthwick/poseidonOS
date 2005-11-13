#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <fat.h>
#include <kmalloc.h>
#include <string.h>

FILE *fopen(char *path, char *mode)
{
	vfs_mount vmount;
	char relative_path[strlen(path)];

	vfs_mount_parse(path, relative_path, &vmount);

	return vmount.fopen(&vmount, path, mode);
}

int fclose(FILE *file)
{
	vfs_mount *vmount;
	fat_fclose(vmount, file);

	return 1;
}

int fgetc(FILE *file)
{
	vfs_mount *vmount;
	return fat_getchar(vmount, file);
}

long int ftell(FILE *file)
{
	return file->offset;
}

/***********************************************
 * int fseek(FILE *file, long int offset, int start)
 *
 * This comes straight from the ANSI C documentation.
 * *********************************************/
int fseek(FILE *file, long int offset, int start)
{
	switch (start)
	{
		case SEEK_CUR:
				break;
		case SEEK_END:
				file->offset = file->size;
				break;
		case SEEK_SET:
				file->offset = 0;
				break;
		default:
				return 1;
	}

	file->offset += offset;
	return 0;
}

