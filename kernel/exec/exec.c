#include <ktypes.h>
#include <kdebug.h>

#include <vfs.h>
#include <exec.h>

#include <screen.h>
#include <multitasking.h>

#include <mm/virtual_mem.h>

/*****************************************
 * int exec(char *exe)
 *
 * runs a program that is on the disk.  Returns the status code from the program
 * */
static void test();
int exec(char *exe) {
	FILE *file;
	char ch;
	char *program;
	int i = 0;
	page_t page;
	int *(*exe_image)(void);
	int ret;
  int count = 0;
  process_t *task;

	file = fopen(exe, "r");

	if (file == NULL) {
		return -1;
	}

	//get a virtual page for this process in userspace
	page.count = 3;
	mm_virtual_page_alloc(&page);
	program = (char *)page.address;

	/*copy the file into a buffer*/
  for (count = 0; count < 55; count++) {
	  ch  = (char)fgetc(file);
		program[count] = ch;
	}


	fclose(file);

	/*execute the program*/
	task = multitasking_process_new(program, exe, PRIORITY_LOW, PROCESS_DRIVER);
	multitasking_process_add(task);

  KDEBUG("added task");

  /*
  kprint("returned value: ");
  put_int(ret, 10);
  kprint("\n");

	mm_virtual_page_free(&page);

	return ret;
  */
  return 5;
}

static void test() {
  asm("int $0x45");
  kprint("hello world!");
  while(1);
}


