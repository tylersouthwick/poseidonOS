global libc_isr
extern libc_handler

libc_isr:
	pushad
	push ebx
	push eax
	call libc_handler
	popad
	iret
