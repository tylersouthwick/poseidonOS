;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; gdt.asm
;;
;; implements gdt structures
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[bits 32]

[global gdt_kernel_code]
[global gdt_kernel_data]
[global gdt_user_code]
[global gdt_user_data]
[global gdt_tss]
[global gdt_asm_init]

;;;;;;;;
;; loads the gdt and loads cs with the kernel_code segment (0x08)
gdt_asm_init:
	cli
	lgdt[GDTR]
	sti
	;; the first gdt entry must be the kernel_code segment!
	jmp 0x08:gdt_init_continue

gdt_init_continue:
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; GDT structures
GDTR:
GDTsize	DW GDT_END-GDT
GDTbase	dd GDT

;;;;;;;;;
;; A gdt entry is setup as follows
; byte | name    |  description 
;   0  | limit   |  [0-7]
;   1  | limit   |  [8-15]
;	  2  | base    |  [0-7]
;	  3  | base    |  [8-15]
;	  4  | base    |  [16-23]
;	  5  | type    |
;	  6  | flags [& limit
;	  7  | base    |  [24-31]

[global GDT]
GDT:
NULL_SEL	EQU $-GDT
	dd 0x0
	dd 0x0

;;;;;;;;;;;;;;;;;;;;;;;;;;kernel GDT entries;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;0x0 - 0x100000 (1 GB)
KERNEL_CODE		EQU $-GDT
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0x9A
	db 0xCF
	db 0x0
KERNEL_DATA	EQU $-GDT
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0x92
	db 0xCF
	db 0x0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;User GDT entries;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 0x400001 - 0xFFFFFF
USER_CODE	EQU $-GDT
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0xFA
	db 0xCF
	db 0x0
USER_DATA	EQU $-GDT
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0xF2
	db 0xCF
	db 0x0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;TSS segment entry;;;;;;;;;;;;;;;;;;;;;;
TSS_SEL EQU $-GDT
	dw 0xFFFF
	db 0x90
	db 0x89
	db 0xFF
	dw 0x00
	dw 0x00
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;TSS segment entry;;;;;;;;;;;;;;;;;;;;;;
TSS_SEL2 EQU $-GDT
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0x92
	db 0xCF
	db 0x0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GDT_END:

;;;;;;;;;;;;;;;;;;;;;;;;;;;; export GDT selector values ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
gdt_kernel_code: dd KERNEL_CODE
gdt_kernel_data: dd KERNEL_DATA
gdt_user_code: dd USER_CODE
gdt_user_data: dd USER_DATA
gdt_tss: dd TSS_SEL
