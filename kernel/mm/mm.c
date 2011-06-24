#include <mm/mm.h>
#include <mm/physical.h>
#include <multiboot.h>
#include <kdebug.h>
#include <mm/paging.h>

void mm_init(multiboot_info_t *mm_info) {
	INFO(("Initializing Memory Management"));

	mm_physical_init(mm_info);

	mm_paging_init();

	/* tests the page fault code
	char *test = 0x4000000;
	test[0] = 'd';
	test[1] = 0;
	DEBUG(("test: %s", test));
	*/
}
