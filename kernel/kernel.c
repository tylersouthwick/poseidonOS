#include <kutil.h>

#include <vfs.h>
#include <exec.h>
#include <mm/virtual_mem.h>
#include <mm/mm.h>
#include <kmalloc.h>
#include <idt.h>
#include <gdt.h>
#include <screen.h>
#include <drivers.h>
#include <devices/manager.h>
#include <multitasking.h>
#include <util/map.h>
#include <kdebug.h>

/*this is for the system as a whole so that the current IRQ mask can be tracked*/
unsigned int irq_mask=0;

/*this is the external pointer to whatever the current process is.  It can be 
 * treated much like the 'this' pointer in Java or C++.*/
extern process_t *current_process;

static bool shutdown = false;

void do_shutdown(void);
void k_main(unsigned long, multiboot_info_t *);
void kernel_init(void);
void init(void);

/********************************************************************************
* void k_main(unsigned long magic, multiboot_info_t *mm_info)
*
* This is the main entry point into the kernel.  Its at this point that the control
* of the system is passed from the boot loader to the kernel.
*
* Parameters:
*   1) unsigned long magic
*        This is a "magic" value passed from any multiboot complient bootloader.
*        It must equal the magic value from the grub definitions
*   2) multiboot_info_t *mm_info
*        This must be a valid pointer to a multiboot structure
*
* Return value:
*   none
*
* Preconditions
*   This is a PROTECTED MODE kernel.  Therefore, before control is passed to it, 
*   the A20 Gate must be enabled and 32-bit Protect Mode must be enabled.  Execution
*   will just stop if the system is not running in 32-bit Protected Mode.
**********************************************************************************/
void k_main(unsigned long magic, multiboot_info_t *mm_info) {
	screen_clear();
	screen_set_color(SCREEN_FG_YELLOW | SCREEN_BG_BLACK);
	kprint("PoseidonOS v0.1 testing\n\n");
	screen_set_color(SCREEN_DEFAULT);

  /*
	kprint("Setting up IDT...");
	idt_setup();
	screen_set_color(SCREEN_FG_GREEN | SCREEN_BG_BLACK);
	kprint("ok\n");
	screen_set_color(SCREEN_DEFAULT);

	kprint("Initilizing MM...");
	mm_init(mm_info);
	screen_set_color(SCREEN_FG_GREEN | SCREEN_BG_BLACK);
	kprint("ok\n");
	screen_set_color(SCREEN_DEFAULT);

	kprint("Initilizing new GDT...");
	gdt_init();
	screen_set_color(SCREEN_FG_GREEN | SCREEN_BG_BLACK);
	kprint("ok\n");
	screen_set_color(SCREEN_DEFAULT);
	
	kprint("Starting devicemanager...");
	devicemanager_init();
	screen_set_color(SCREEN_FG_GREEN | SCREEN_BG_BLACK);
	kprint("ok\n");
	screen_set_color(SCREEN_DEFAULT);

	kprint("Entering multitasking environment...\n");
	multitasking_init();
  */
}

/***************************************************************
 * void kernel_init()
 * 
 * This process finishes loading all the kernel subsystems once
 * multitasking has been started.  This process must start the
 * system_init process before it finishes, or else the system will
 * just hang and do nothing (there will only be the system idle 
 * process running
 * 
 * Author	: Tyler Southwick (northfuse@gmail.com)
 * Date		: December 30, 2004
 * **************************************************************/
void kernel_init() {
  /*
	int drivers_count;
	int status;
	
	screen_set_color(SCREEN_FG_BRIGHT_BLUE | SCREEN_BG_BLACK);
	kprint("\nEntered multitasking environment!\n");
	screen_set_color(SCREEN_DEFAULT);

	kprint("initilizing devices..");
	devicemanager_init_devices();
	kprint("\n");

	vfs_init();

	kprint("mounting root filesystem (read-only) at / ...");
	status = mount("fd0", "/", "fat");
	if (status == -1) {
		screen_set_color(SCREEN_FG_RED | SCREEN_BG_BLACK);
		kprint("unable to mount root fs\n");
		screen_set_color(SCREEN_DEFAULT);
		do_shutdown();
	}
	kprint("\n");

	kprint("installing userspace interrupts....");
	idt_user_setup();
	screen_set_color(SCREEN_FG_GREEN | SCREEN_BG_BLACK);
	kprint("ok\n");
	screen_set_color(SCREEN_DEFAULT);

	kprint("loading drivers...");
	drivers_count = drivers_load();
	screen_set_color(SCREEN_FG_GREEN | SCREEN_BG_BLACK);
	kprint("loaded ");
	put_int(drivers_count, 10);
	kprint(" driver(s)\n");
	screen_set_color(SCREEN_DEFAULT);

	kprint("\nStarting shell.app...\n");
	status = exec("/shell.app");
	if (status == -1) {
		kprint("unable to find /shell.app\n");
	}

	while (!shutdown);

	do_shutdown();
	while(1);
  */
}

void init() {
				/*
	while(1)
	{
		kprint("init!");
		sleep(10);
	}
	*/
				while(1);
}

void do_shutdown() {
	screen_set_color(SCREEN_FG_MAGENTA | SCREEN_BG_BLACK);
	kprint("\n\nSystem Shutting Down!\n");
	screen_set_color(SCREEN_DEFAULT);
	kprint("\tumounting all drives...");
	//umount_all();

	screen_set_color(SCREEN_FG_YELLOW | SCREEN_BG_BLACK);
	kprint("\n\tSystem Halted");

	while(1);
}
