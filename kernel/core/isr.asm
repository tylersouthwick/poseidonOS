[global isr0]
isr0:
    pusha
    push gs
    push fs
    push ds
    push es
    
    extern interrupt0
    call interrupt0

    pop es
    pop ds
    pop fs
    pop gs
    popa
    iret

[global keyboard_isr]
keyboard_isr:
    pusha
    push gs
    push fs
    push ds
    push es
    
    extern keyboard_interrupt
    call keyboard_interrupt

    pop es
    pop ds
    pop fs
    pop gs
    popa
    iret

