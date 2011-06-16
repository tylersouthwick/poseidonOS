#include <mm/mm.h>
#include <mm/physical.h>
#include <kdebug.h>

void mm_init(multiboot_info *mbt) {
	INFO(("Initializing Memory Management"));

	mm_physical_init(mbt);
}
