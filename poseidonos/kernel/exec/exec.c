#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <exec.h>

#include <mm/virtual_mem.h>

/*this is implemented in exec.asm*/
extern void exec_asm(void *);

int exec(char *exe)
{
	FILE *file;
	char ch;
	char *program;
	int i = 0;

	file = fopen(exe, "r");

	if (file == NULL)
		return -1;

	//get a virtual page for this process in userspace
	program = mm_virtual_page_alloc();
	/*
	kprint("allocating userspace address: ");
	put_int(program, 16);
	kprint("\n");
	*/

	/*copy the buffer into a buffer*/
	program = kmalloc(fgetsize(file));
	while ((ch  = getchar(file)) != EOF)
		program[i++] = ch;

	fclose(file);

	/*execute the program*/
	kprint("executing program\n");
	//exec_asm(program);
	kprint("executing program finished\n");

	return 0;
}

