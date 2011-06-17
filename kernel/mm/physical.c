#include <mm/physical.h>
#include <multiboot.h>
#include <kdebug.h>
#include <string.h>

static void mm_physical_summary(multiboot_info_t *mm_info);

void mm_physical_init(multiboot_info_t *mm_info) {
	mm_physical_summary(mm_info);
}

#define memory_display(type, amount) if (amount) {DEBUG(("%s Memory: %dkb", type, (amount) >> 10));}

static void mm_physical_summary(multiboot_info_t *mm_info) {
	int size = 0, i = 0;
	unsigned long free, reserved, acpi_reclaimable, acpi_nvs, bad;
	char memory_type[255];

	memory_map_t *mmap = (memory_map_t *) (mm_info->mmap_addr);

	free = reserved = acpi_reclaimable = acpi_nvs = bad = 0;

	while((unsigned long) mmap < mm_info->mmap_addr + mm_info->mmap_length) {
		strcpy(memory_type, "");
		switch(mmap->type) {
			case MEM_USABLE:
				strcpy(memory_type, "Free");
				free += mmap->length_low;
				break;
			case MEM_RESERVED:
				strcpy(memory_type, "Reserved");
				reserved += mmap->length_low;
				break;
			case MEM_ACPI:
				strcpy(memory_type, "ACPI Reclaimable");
				acpi_reclaimable += mmap->length_low;
				break;
			case MEM_ACPI_NVS:
				strcpy(memory_type, "ACPI NVS");
				acpi_nvs += mmap->length_low;
				break;
			case MEM_BAD:
				bad += mmap->length_low;
				strcpy(memory_type, "Bad");
				break;
		}
		if (mmap->length_high) {
			ERROR(("There is high mem for %s.... fix this", memory_type));
		}
		DEBUG(("0x%08x -> %db: %s", mmap->base_addr_low, mmap->length_low, memory_type));
		mmap = (memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size));
	}

	memory_display("Free", free);
	memory_display("Reserved", reserved + acpi_reclaimable + acpi_nvs);
	memory_display("Bad", bad);
}
