;  File: idt.asm
;  Description: Implements Interrupt Descriptor Table access

[extern int_00]
[global isr00]
isr00:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_00
	pop gs
	pop fs
	pop es
	pop ds
	popa
	;because the divide by zero interrupt is called *before* the instruction
	;the execution address needs to be advaced to after the error
	;this really should be changed, as it might cause unpleasent problems for programs,
	;but it will work for now
	inc word [esp]
	inc word [esp]
	iret

[extern int_01]
[global isr01]
isr01:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_01
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_02]
[global isr02]
isr02:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_02
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_03]
[global isr03]
isr03:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_03
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_04]
[global isr04]
isr04:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_04
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_05]
[global isr05]
isr05:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_05
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_06]
[global isr06]
isr06:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_06
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_07]
[global isr07]
isr07:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_07
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_08]
[global isr08]
isr08:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_08
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_09]
[global isr09]
isr09:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_09
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_10]
[global isr10]
isr10:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_10
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_11]
[global isr11]
isr11:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_11
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_12]
[global isr12]
isr12:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_12
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_13]
[global isr13]
isr13:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_13
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_14]
[global isr14]
isr14:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	;mov eax,[ebp+48]
	;mov ebx,[ebp+52]
	;mov ecx,[ebp+56]
	;push ecx
	;push ebx
	;push eax
	call int_14
	;pop eax
	;pop ebx
	;pop ecx
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_16]
[global isr16]
isr16:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_16
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_17]
[global isr17]
isr17:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_17
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_18]
[global isr18]
isr18:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_18
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret

[extern int_19]
[global isr19]
isr19:
	pusha
	push ds
	push es
	push fs
	push gs
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	cld
	call int_19
	pop gs
	pop fs
	pop es
	pop ds
	popa
	iret
