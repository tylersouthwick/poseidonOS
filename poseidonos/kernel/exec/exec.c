#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>

int exec(char *exe)
{
	FILE *file;
	char ch;
	char *program;
	int i = 0;

	file = fopen(exe, "r");

	if (file == NULL)
		return -1;

	/*copy the buffer into a buffer*/
	program = kmalloc(fgetsize(file));
	while ((ch  = getchar(file)) != EOF)
		program[i++] = ch;

	fclose(file);

	/*execute the program*/
	exec_asm(program);

	return 0;
}

