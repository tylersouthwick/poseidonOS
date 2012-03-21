global libc_isr
extern libc_handler

libc_isr:
	pushad
	push gs
	push fs
	push ds
	push es
	push ebx
	push eax
	call libc_handler
	add esp, 8 ;increment the stack to get rid of ebx and eax
	pop es
	pop ds
	pop fs
	pop gs
	popad
	iret
