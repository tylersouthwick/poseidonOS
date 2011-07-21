#include <kdebug.h>
#include <screen.h>
#include <core/gdt.h>
#include <core/idt.h>
#include <version.h>
#include <string.h>
#include <multitasking/multitasking.h>
#include <multiboot.h>
#include <mm/mm.h>
#include <devices/manager.h>
#include <vfs.h>
#include <mutex.h>

void kmain(multiboot_info_t *mm_info);
void shutdown();
static void kernel_init();

void kmain(multiboot_info_t *mm_info) {
    initScreen();
    clear_screen();
    INFO(("Booting PoseidonOS v%s", KERNEL_VERSION));

    idt_setup();

    gdt_init();

    mm_init(mm_info);

    multitasking_init(kernel_init);

    FATAL(("shouldn't get here!"));

    while(1);
}

static void kernel_init() {
	DEBUG(("Entered multitasking environment"));
	INFO(("Initializing Kernel Subsystems"));

#ifdef INTEGRATION_TESTS
	mutex_test();
#endif

	devicemanager_init();

	vfs_init();

	INFO(("Mounting root filesystem (read-only) at /"));
	int status = mount("fd0", "/", "fat");
	if (status == -1) {
		ERROR(("Unable to mount root"));
		shutdown();
		return;
	}
	INFO(("Mounted root filesystem (read-only) at /"));

	while(1);
}

void shutdown() {
	__asm__ volatile ("cli");
	INFO(("System Shutting Down"));

	INFO(("Unmounting all devices"));
	umount_all();

	INFO(("System Halted"));

	__asm__ volatile ("hlt");

	//shouldn't be needed.. just in case
	while(1);
}
