;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; gdt.asm
;;
;; implements gdt structures
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[bits 32]

[global gdt_flush]
[extern gdt_table]
gdt_flush:
  lgdt [gdt_table]
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:flush2

flush2:
  ret

