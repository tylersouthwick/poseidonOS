OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
SECTIONS
{
	. = 0x100000;
	_kernel_start = .;

	.text :
	{
		*(.text)
		*(.rodata)
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

	_kernel_end = .;
}

