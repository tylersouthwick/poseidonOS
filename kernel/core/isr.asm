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

[global isr_empty]
isr_empty:
    pusha
    push gs
    push fs
    push ds
    push es
    
    extern empty_interrupt
    call empty_interrupt

    pop es
    pop ds
    pop fs
    pop gs
    popa
    iret
