[global mm_page_fault_isr]
mm_page_fault_isr:
    pusha
    push gs
    push fs
    push ds
    push es
    
    extern mm_page_fault_int
    push eax
    call mm_page_fault_int

    pop es
    pop ds
    pop fs
    pop gs
    popa
    iret
