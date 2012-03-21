#define TRACE
#include <multitasking/multitasking.h>
#include <kdebug.h>
#include <mm/sbrk.h>
#include <mm/paging.h>
#include <string.h>
#include <vfs.h>
#include <exec.h>
#include <exec/elf.h>

int spawn_program(char *exeName, unsigned char *exeFileData, exe_format_t *exe) {
	DEBUG_MSG(("spawning exe"));

	unsigned long start_address = 999999999;
	unsigned long end_address = 0;
	for (int i = 0; i < exe->numSegments; ++i) {
		exe_segment_t *segment = &exe->segments[i];
		if (segment->startAddress == 0) continue;

		if (segment->startAddress < start_address) {
			start_address = segment->startAddress;
		}
		const unsigned long logical_end = segment->startAddress + segment->sizeInMemory;
		if (end_address < logical_end) {
			end_address = logical_end;
		}
	}
	const int size = end_address - start_address;
	DEBUG_MSG(("virtual address: 0x%x-0x%x [%i bytes]", start_address, end_address, size));

	unsigned long cr3 = mm_virtual_mem_new_address_space();
	TRACE_MSG(("Created new cr3: 0x%x", cr3));

	int status = mm_alloc_virtual_address_range(cr3, start_address, size);
	if (status != 0) {
		ERROR_MSG(("Unable to allocate virtual address range"));
		return 1;
	}
	TRACE_MSG(("Allocated virtual address range: 0x%x", start_address));

	((char *)start_address)[0] = 'h';
	TRACE_MSG(("test writing: %c", (char *)start_address));

	/* Load segment data into memory */
	DEBUG_MSG(("Loading %i segments into memory", exe->numSegments));
	for (int i = 0; i < exe->numSegments; ++i) {
		exe_segment_t *segment = &exe->segments[i];
#ifdef DEBUG
		DEBUG_MSG(("segment %i:", i));
		DEBUG_MSG(("\tstartAddress: 0x%x", segment->startAddress));
		DEBUG_MSG(("\tlength: %i", segment->lengthInFile));
#endif

		if (segment->lengthInFile)
		memcpy((char *) segment->startAddress,
			exeFileData + segment->offsetInFile,
			segment->lengthInFile);
	}

	DEBUG_MSG(("creating process"));
	process_t *process =  multitasking_process_new(exe->entryAddr, exeName, PRIORITY_HIGH, 0);
	process->cr3 = cr3;
	DEBUG_MSG(("adding process"));
	multitasking_process_add(process);

	return 0;
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
			int spawn_status = spawn_program(path, f->data, &exe);
			if (spawn_status != 0) {
				ERROR_MSG(("Unable to spawn program"));
			}
		} else {
			ERROR_MSG(("Unable to load elf file: %i", status));
		}
		fclose(f);
	}
}

void exec(void (*process)()) {
	process();
}
