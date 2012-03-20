#include <exec/elf.h>
#include <exec.h>
#include <kdebug.h>
#include <string.h>

static int elf_validate(elf_header_t *header) {
	//check magic numbers
	elf_ident_t *ident = (elf_ident_t *) header->ident;
	char *magic = ident->magic;
	DEBUG_MSG(("checking ident [%s]", header->ident));
	if (!(magic[0] == 0x7f && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F')) {
		return ELF_INVALID_HEADER_MAGIC;
	}

#ifdef DEBUG
	switch (ident->ei_class) {
		case ELFCLASS32:
			DEBUG_MSG(("32-bit objects"));
			break;
		case ELFCLASS64:
			DEBUG_MSG(("64-bit objects"));
			break;
		default:
			DEBUG_MSG(("ELF Class invalid"));
			break;
	}
#endif

	if (ident->ei_class != ELFCLASS32) {
		ERROR_MSG(("Can only handle 32 bit elf binaries"));
		return ELF_INVALID_HEADER_32_BITS;
	}

#ifdef DEBUG
	switch (ident->ei_data) {
		case ELFDATA2LSB:
			DEBUG_MSG(("LSB encoding"));
			break;
		case ELFDATA2MSB:
			DEBUG_MSG(("MSB encoding"));
			break;
		default:
			DEBUG_MSG(("ELF Data Encoding Invalid"));
			break;
	}
#endif

	if (ident->ei_data != ELFDATA2LSB && ident->ei_data != ELFDATA2MSB) {
		ERROR_MSG(("Invalid data encoding"));
		return ELF_INVALID_HEADER_ENCODING;
	}

#ifdef DEBUG
	DEBUG_MSG(("ELF version: %i", ident->ei_version));
#endif

	return 0;
}

static int elf_parse_program_header(elf_program_header_t *header, exe_segment_t *segment) {
#ifdef DEBUG
	DEBUG_MSG(("Program Header"));
	char type[25];
	switch (header->type) {
		case PT_NULL:
			strcpy(type, "null");
			break;
		case PT_LOAD:
			strcpy(type, "load");
			break;
		case PT_DYNAMIC:
			strcpy(type, "dynamic");
			break;
		case PT_INTERP:
			strcpy(type, "interp");
			break;
		case PT_NOTE:
			strcpy(type, "note");
			break;
		case PT_SHLIB:
			strcpy(type, "shlib");
			break;
		case PT_PHDR:
			strcpy(type, "phdr");
			break;
		case PT_LOPROC:
			strcpy(type, "loproc");
			break;
		case PT_HIPROC: 
			strcpy(type, "hiproc");
			break;
		default:
			strcpy(type, "unknown");
			break;
	}
	DEBUG_MSG(("\ttype: %s [%i]", type, header->type));
	DEBUG_MSG(("\toffset: %i", header->offset));
	DEBUG_MSG(("\tsize: %i", header->memSize));
	DEBUG_MSG(("\tstartAddress: %i", header->vaddr));
#endif

	if (header->type == PT_NULL) {
		ERROR_MSG(("Invalid program header [null]"));
		return -1;
	}

	segment->offsetInFile = header->offset;
	segment->lengthInFile = header->fileSize;
	segment->startAddress = header->vaddr;
	segment->sizeInMemory = header->memSize;
	return 0;
}

static int elf_parse_program_headers(elf_header_t *header, exe_format_t *exe) {
	DEBUG_MSG(("program headers:"));
	DEBUG_MSG(("\toffset: 0x%x", header->phoff));
	DEBUG_MSG(("\tnum: %i", header->phnum));

	if (header->phnum > EXE_MAX_SEGMENTS) {
		ERROR_MSG(("Invalid program headers. Found %i can only have %i.", header->phnum, EXE_MAX_SEGMENTS));
		return -1;
	}

	exe->numSegments = header->phnum;
	DEBUG_MSG(("base: 0x%x", header));
	DEBUG_MSG(("offset: %i", header->phoff));
	unsigned int headers = ((unsigned int) header) + header->phoff;
	DEBUG_MSG(("headers: 0x%x", headers));
	DEBUG_MSG(("program header size: %i", header->phentsize));
	for (int i = 0; i < exe->numSegments; i++) {
		elf_program_header_t *programHeader = (elf_program_header_t *)(headers + (i * header->phentsize));
		exe_segment_t *segment = &(exe->segments[i]);
		int rc = elf_parse_program_header(programHeader, segment);
		if (rc != 0) {
			ERROR_MSG(("Invalid program header"));
			return rc;
		}
	}

	return 0;
}

int elf_parse(unsigned char *data, int size, exe_format_t *exe) {
	int rc;
	DEBUG_MSG(("parsing elf file [%i bytes]", size));
	elf_header_t *header = (elf_header_t *)data;
	rc = elf_validate(header);
	if (rc != 0) {
		ERROR_MSG(("Invalid header"));
		return rc;
	}
	DEBUG_MSG(("valid header"));

	rc = elf_parse_program_headers(header, exe);
	if (rc != 0) {
		ERROR_MSG(("Invliad program headers"));
		return rc;
	}

	exe->entryAddr = header->entry;
	DEBUG_MSG(("ELF entry: 0x%x", exe->entryAddr));
	return 0;
}
