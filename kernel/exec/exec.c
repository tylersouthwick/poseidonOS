#include <multitasking/multitasking.h>
#include <kdebug.h>
#include <mm/sbrk.h>
#include <mm/paging.h>
#include <string.h>
#include <vfs.h>
#include <exec.h>
#include <exec/elf.h>

void spawn_program(char *exeName, unsigned char *exeFileData, exe_format_t *exe) {
	DEBUG_MSG(("spawning exe"));

	ulong_t size = 0;
	for (int i = 0; i < exe->numSegments; ++i) {
		exe_segment_t *segment = &exe->segments[i];
		size += segment->sizeInMemory;
	}
	DEBUG_MSG(("max virtual address: 0x%x", size));
	unsigned long *cr3 = mm_virtual_mem_new_address_space();
	unsigned long *virtSpace = exe->entryAddr;
	int status = mm_alloc_virtual_address_range(cr3, exe->entryAddr, size);
	if (status != 0) {
		ERROR_MSG(("Unable to allocate virtual address range"));
		return 1;
	}
	DEBUG_MSG(("virtSpace: 0x%x", virtSpace));
	memset((char *) virtSpace, '\0', size);

	/* Load segment data into memory */
	DEBUG_MSG(("Loading %i segments into memory", exe->numSegments));
	for (int i = 0; i < exe->numSegments; ++i) {
		exe_segment_t *segment = &exe->segments[i];
#ifdef DEBUG
		DEBUG_MSG(("segment %i:", i));
		DEBUG_MSG(("\tstartAddress: %i", segment->startAddress));
		DEBUG_MSG(("\tlength: %i", segment->lengthInFile));
#endif

		memcpy(virtSpace + segment->startAddress,
			exeFileData + segment->offsetInFile,
			segment->lengthInFile);
	}

	DEBUG_MSG(("creating process"));
	process_t *process =  multitasking_process_new(exe->entryAddr, exeName, PRIORITY_HIGH, 0);
	process->cr3 = cr3;
	DEBUG_MSG(("adding process"));
	multitasking_process_add(process);
}

void exec_path(char *path) {
	DEBUG_MSG(("exec path: %s", path));
	FILE *f = fopen(path, "r");
	if (f == NULL) {
		ERROR_MSG(("path not found: %s. Unable to execute.", path));
	} else {
		DEBUG_MSG(("opened file"));
		exe_format_t exe;
		int status = elf_parse(f->data, f->size, &exe);
		if (status == 0) {
			spawn_program(path, f->data, &exe);
		} else {
			ERROR_MSG(("Unable to load elf file: %i", status));
		}
		fclose(f);
	}
}

void exec(void (*process)()) {
	process();
}
