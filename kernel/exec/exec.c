#include <multitasking/multitasking.h>
#include <kdebug.h>
#include <mm/sbrk.h>
#include <string.h>
#include <vfs.h>
#include <exec.h>
#include <exec/elf.h>

void spawn_program(char *exeName, unsigned char *exeFileData, struct Exe_Format *exe) {
	DEBUG_MSG(("spawning exe"));

	ulong_t maxva = 0;
	for (int i = 0; i < exe->numSegments; ++i) {
		struct Exe_Segment *segment = &exe->segmentList[i];
		ulong_t topva = segment->startAddress + segment->sizeInMemory;

		if (topva > maxva) {
			maxva = topva;
		}
	}
	DEBUG_MSG(("max virtual address: 0x%x", maxva));
	void *virtSpace = sbrk(maxva);
	DEBUG_MSG(("virtSpace: 0x%x", virtSpace));
	memset((char *) virtSpace, '\0', maxva);

	/* Load segment data into memory */
	DEBUG_MSG(("Loading segments into memory"));
	for (int i = 0; i < exe->numSegments; ++i) {
		struct Exe_Segment *segment = &exe->segmentList[i];

		memcpy(virtSpace + segment->startAddress,
			exeFileData + segment->offsetInFile,
			segment->lengthInFile);
	}

	DEBUG_MSG(("creating process"));
	process_t *process =  multitasking_process_new(exe->entryAddr, exeName, PRIORITY_HIGH, 0);
	multitasking_process_add(process);
}

void exec_path(char *path) {
	DEBUG_MSG(("exec path: %s", path));
	FILE *f = fopen(path, "r");
	if (f == NULL) {
		ERROR_MSG(("path not found: %s. Unable to execute.", path));
	} else {
		DEBUG_MSG(("opened file"));
		struct Exe_Format exe;
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
