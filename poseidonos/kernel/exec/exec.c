#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <exec.h>

#include <screen.h>

#include <mm/virtual_mem.h>

/*this is implemented in exec.asm*/
extern void exec_asm(void *);

/*****************************************
 * int exec(char *exe)
 *
 * runs a program that is on the disk.  Returns the status code from the program
 * */
int exec(char *exe) {
	FILE *file;
	char ch;
	char *program;
	int i = 0;
	page_t page;
	void *(*exe_image)(void);
	int ret;

	kprint("opening file....");
	file = fopen(exe, "r");
	kprint("ok\n");

	if (file == NULL) {
		return -1;
	}

	//get a virtual page for this process in userspace
	page.count = 1;
	kprint("allocating page...");
	mm_virtual_page_alloc(&page);
	kprint("ok\n");
	program = (char *)page.address;

	/*copy the buffer into a buffer*/
	while ((ch  = (char)fgetc(file)) != EOF) {
		program[i++] = ch;
	}

	kprint("the program is ");
	put_int(i, 10);
	kprint(" bytes long\n");

	fclose(file);

	/*execute the program*/
	exe_image = (void *)program;
	ret = (int)exe_image();

	mm_virtual_page_free(&page);

	return ret;
}

