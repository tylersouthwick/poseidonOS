;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; gdt_wrapper.asm
;;
;; low-level gdt routines (loading a new selector table)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[bits 32]

[global gdt_load]
gdt_load:
  mov eax, [esp+4]
  lgdt [eax]
  jmp 0x08:flush

flush:
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  ret

