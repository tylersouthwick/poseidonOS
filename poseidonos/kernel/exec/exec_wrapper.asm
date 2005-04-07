[global exec_asm]
%define program ebp+8
exec_asm:
	push ebp
	mov ebp, esp

	mov eax, [program]
	call eax

	pop ebp
	ret
