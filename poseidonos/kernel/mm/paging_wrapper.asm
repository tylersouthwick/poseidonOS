;file: paging.asm
;description: allow rw access to control registers

[global read_cr0]
read_cr0
	mov eax, cr0
	ret

[global write_cr0]
write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
	ret

[global read_cr2]
read_cr2:
	mov eax, cr2
	ret

[global read_cr3]
read_cr3:
	mov eax, cr3
	ret

[global write_cr3]
write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	ret

[global paging_flush_cache]
paging_flush_cache:
	mov eax, cr3
	mov cr3, eax
	ret
