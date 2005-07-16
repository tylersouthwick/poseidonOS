OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
SECTIONS
{
	. = 0x300000;
	_kernel_start = .;

	.text :
	{
		*(.text)
	}

	.data ALIGN (0x1000) :
	{
		*(.data)
	}

	.rodata :
	{
		*(.rodata)
	}

	.bss :
	{
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}

	_kernel_end = .;/*0x00000030;*/
}

