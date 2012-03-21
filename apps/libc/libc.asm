global libc_clear_screen
libc_clear_screen:
	mov ebx, [esp+4]
	mov eax, 0
	int 128
	ret

global libc_write_string
libc_write_string:
	mov ebx, [esp+4]
	mov eax, 1
	int 128
	ret

