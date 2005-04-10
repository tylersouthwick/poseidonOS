#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <exec.h>

/*this is implemented in exec.asm*/
void exec_asm(void *);

int exec(char *exe)
{
	FILE *file;
	char ch;
	char *program;
	int i = 0;

	file = fopen(exe, "r");

	if (file == NULL)
		return -1;


	//get a virtual page for this process in userspac
	program = mm_virtual_page_alloc();
	kprint("allocating userspace address: ");
	put_int((int)program, 16);
	kprint("\n");
	kprint("testing....");
	program[0] = 'd';

	/*copy the buffer into a buffer*/
	program = kmalloc(fgetsize(file));
	while ((ch  = getchar(file)) != EOF)
		program[i++] = ch;

	fclose(file);

	/*execute the program*/
	exec_asm(program);

	return 0;
}

