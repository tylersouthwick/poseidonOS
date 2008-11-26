[global setup_tss]
[extern gdt_tss]
[extern put_int]

%define tss ebp+12
setup_tss
	push ebp
	push eax
	mov ebp, esp

	mov eax, [tss]
	ltr [tss]

	pop eax
	pop ebp
	ret

