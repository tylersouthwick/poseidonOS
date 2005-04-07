#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <fat.h>

FILE *fopen(char *path, char *mode)
{
	return  fat_fopen(path, mode);
}

void fclose(FILE *file)
{
	fat_fclose(file);
}

