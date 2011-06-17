#include <mm/physical.h>
#include <multiboot.h>
#include <kdebug.h>

static void mm_physical_summary(multiboot_info_t *mm_info);

void mm_physical_init(multiboot_info_t *mm_info) {
	mm_physical_summary(mm_info);
}

static void mm_physical_summary(multiboot_info_t *mm_info) {
	int size = 0, i = 0;
	unsigned long long int free, reserved, acpi_reclaimable, acpi_nvs, bad;
	char memory_type[255];

	memory_map_t *mmap = (memory_map_t *) (mm_info->mmap_addr);

	free = reserved = acpi_reclaimable = acpi_nvs = bad = 0;

	while((unsigned long) mmap < mm_info->mmap_addr + mm_info->mmap_length) {
		strcpy(memory_type, "");
		switch(mmap->type) {
			case MEM_USABLE:
				strcpy(memory_type, "Free");
				//free += mmap->length;
				break;
			case MEM_RESERVED:
				strcpy(memory_type, "Reserved");
				break;
			case MEM_ACPI:
				strcpy(memory_type, "ACPI Reclaimable");
				break;
			case MEM_ACPI_NVS:
				strcpy(memory_type, "ACPI NVS");
				break;
			case MEM_BAD:
				strcpy(memory_type, "Bad");
				break;
		}
		DEBUG(("0x%x%x -> 0x%x%x: %s", mmap->base_addr_low, mmap->base_addr_high, mmap->length_low, mmap->length_high, memory_type));
		mmap = (memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size));
	}

	DEBUG(("Free Memory: %i", free));
}
