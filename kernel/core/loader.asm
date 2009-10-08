global start    ;making entry point visible to linker
extern kmain    ;kmain is defined elsewhere
extern call_cpp_constructors
extern call_cpp_destructors

; setting up the Multiboot header - see GRUB docs for details
MODULE_ALIGN equ 1<<0                    ; align loaded modules on page boundaries
MEMINFO      equ 1<<1                    ; provide memory map
FLAGS        equ MODULE_ALIGN | MEMINFO   ; this is the Multiboot 'flag' field
MAGIC        equ 0x1BADB002              ; 'magic number' lets bootloader find the header
CHECKSUM     equ -(MAGIC + FLAGS)        ; checksum required

section .text
align 4
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

;reserve initial kernel stack space
STACKSIZE equ 0x4000                    ; 16k

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; this is the main 'start' point for the kernel
;;;;;;;;;;;;;;;;;;;;;;
start:
    mov esp, stack+STACKSIZE            ; set up the stack
    push eax                            ; pass Multiboot magic number
    push ebx                            ; pass Multiboot info structure

    call kmain                          ; call the c kernel code

hang:
    hlt                                 ; halt machine should kernel return
    jmp hang

section .bss
align 32
stack:
    resb STACKSIZE                      ; reserve 16k stack on a quadword boundary
