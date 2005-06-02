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
	page_t page;

	file = fopen(exe, "r");

	if (file == NULL)
		return -1;

	//get a virtual page for this process in userspace
	page.count = 1;
	mm_virtual_page_alloc(&page);
	program = (char *)page.address;

	/*copy the buffer into a buffer*/
	while ((ch  = getchar(file)) != EOF)
		program[i++] = ch;

	fclose(file);

	/*execute the program*/
	kprint("executing program\n");
	exec_asm(program);
	kprint("executing program finished\n");

	mm_virtual_page_free(&page);

	return 0;
}

