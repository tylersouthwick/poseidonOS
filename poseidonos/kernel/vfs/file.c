#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <fat.h>

FILE *fopen(char *path, char *mode)
{
	return fat_fopen(path, mode);
}

void fclose(FILE *file)
{
	fat_fclose(file);
}

char getchar(FILE *file)
{
	return fat_getchar(file);
}

int fgetsize(FILE *file)
{
	return file->size;
}

