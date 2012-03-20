#ifndef EXEC_H
#define EXEC_H

#include <ktypes.h>

void exec_path(char *path);
void exec(void (*process)());

/*
 * Bits in flags field of programHeader.
 * These describe memory permissions required by the segment.
 */
#define PF_R	0x4	 /* Pages of segment are readable. */
#define PF_W	0x2	 /* Pages of segment are writable. */
#define PF_X	0x1	 /* Pages of segment are executable. */

/*
 * A segment of an executable.
 * It specifies a region of the executable file to be loaded
 * into memory.
 */
struct Exe_Segment {
    ulong_t offsetInFile;	 /* Offset of segment in executable file */
    ulong_t lengthInFile;	 /* Length of segment data in executable file */
    ulong_t startAddress;	 /* Start address of segment in user memory */
    ulong_t sizeInMemory;	 /* Size of segment in memory */
    int protFlags;		 /* VM protection flags; combination of VM_READ,VM_WRITE,VM_EXEC */
};

#define EXE_MAX_SEGMENTS 3

struct Exe_Format {
    struct Exe_Segment segmentList[EXE_MAX_SEGMENTS]; /* Definition of segments */
    int numSegments;		/* Number of segments contained in the executable */
    ulong_t entryAddr;	 	/* Code entry point address */
};
#endif
