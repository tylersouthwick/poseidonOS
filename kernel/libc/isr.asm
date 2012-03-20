global libc_isr

libc_isr:
	extern libc_handler
	push eax
	push ebx
	call libc_handler
	iret
