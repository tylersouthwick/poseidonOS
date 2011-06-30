[extern floppy_irq]
[global floppy_isr]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void floppy_isr()
;
; This is the floppy Interrupt Service Routine that is invoked
; whenever an irq is fired on line 6.
;
; Author:	Tyler Southwick (northfuse@gmail.com)
; Date:		December 31, 2004
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

floppy_isr:
	; Store state
	cld
	pushad
	push ds
	push es
	push fs
	push gs

	;call the floppy handler
	call floppy_irq

	;send the processor the end of interrupt message (EOI)
	mov al, 0x20
	out 0x20, al
	
	; Restore state
	pop gs
	pop fs
	pop es
	pop ds
	popad
	
	;return from interrupts
	iretd
