global libc_clear_screen
libc_clear_screen:
	pop ebx
	mov eax, 0
	int 128
	ret

global libc_write_string
libc_write_string:
	pop ebx
	mov eax, 1
	int 128
	ret

