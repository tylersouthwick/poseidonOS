; kernel_wrapper.asm
; immediately transfers system control to kernel.c

[bits 32]
[extern k_main]
[global start]

MULTIBOOT_PAGE_ALIGN	equ 1<<0
MULTIBOOT_MEMORY_INFO	equ 1<<1

MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
CHECKSUM		equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

;the multiboot header
align 4
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd CHECKSUM
[extern data]
start:
	push ebx
	push eax

	call k_main
	jmp $

[global gdt_init]
gdt_init:

	ret

.data
GDTR:
GDTsize	DW GDT_END-GDT-1
GDTbase	dd GDT

[global GDT]
GDT:
NULL_SEL	EQU $-GDT
	dd 0x0
	dd 0x0
CODESEL		EQU $-GDT
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0x9A
	db 0xCF
	db 0x0
DATASEL	EQU $-GDT
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0x92
	db 0xCF
	db 0x0
GDT_END:

