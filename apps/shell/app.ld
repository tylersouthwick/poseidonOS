OUTPUT_FORMAT("elf32-i386")
ENTRY(main)

SECTIONS {
	. = 0x300000;
    _kernel_start = .;

    .text : {
        *(.text)
        . = ALIGN(4096);
    }

    .data : {
        start_ctors = .;
        LONG((end_ctors - start_ctors) / 4 - 2) *(.ctors*) LONG(0) end_ctors = .;
        start_dtors = .;
        LONG((end_dtors - start_dtors) / 4 - 2) *(.dtors*) LONG(0) end_dtors = .;
        *(.data)
        . = ALIGN(4096);
    }

    .rodata : {
        *(.rodata)
    }

    .bss : {
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
        . = ALIGN(4096);
    }

    _kernel_end = .;
}
