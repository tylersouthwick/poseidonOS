#include <kernel.h>		/*includes most kernel functions*/
#include <util.h>


/*this is for the system as a whole so that the current IRQ mask can be tracked*/
unsigned int irq_mask=0;

/*this is the external pointer to whatever the current process is.  It can be 
 * treated much like the 'this' pointer in Java or C++.*/
extern process_t *current_process;

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
	int test = 1;
	kprint("PoseidonOS v0.1 testing\n");
	
	kprint("Initilizing new GDT...");
	gdt_init();
	kprint("ok\n");

	kprint("Setting up IDT...");
	idt_setup();
	kprint("ok\n");

	kprint("Initilizing MM...\n");
	mm_init(mm_info);
	kprint("MM Initilized\n");
	
	kprint("Starting devicemanager...");
	devicemanager_init();
	
	kprint("Initilizing multitasking...");
	multitasking_init();
}

void temp_sleep(int mill)
{
	sleep(mill);
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
	process_t *system_init_process;
	
	kprint("starting kernel init....\n");
	drivers_load();
	
	//kprint("mounting root filesystem (read-only) at /\n");
	//mount_root();
	
	while(1);
}
