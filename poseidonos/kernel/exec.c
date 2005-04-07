#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>

int exec(char *exe)
{
	FILE *file;

	file = fopen(exe, "r");
}

