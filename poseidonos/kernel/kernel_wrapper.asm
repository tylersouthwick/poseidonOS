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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; this is the main 'start' point for the kernel
;;;;;;;;;;;;;;;;;;;;;;
start:
	push ebx
	push eax
	call k_main
	jmp $

