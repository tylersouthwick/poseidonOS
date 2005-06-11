#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <fat.h>

FILE *fopen(char *path, char *mode)
{
	vfs_mount vmount;
	char relative_path[strlen(path)];

	vfs_mount_parse(path, relative_path, &vmount);

	return fat_fopen(&vmount, path, mode);
}

void fclose(FILE *file)
{
	vfs_mount *vmount;
	fat_fclose(vmount, file);
}

char getchar(FILE *file)
{
	vfs_mount *vmount;
	return fat_getchar(vmount, file);
}

int fgetsize(FILE *file)
{
	return file->size;
}

