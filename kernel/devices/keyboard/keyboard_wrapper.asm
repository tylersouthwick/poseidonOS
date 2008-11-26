[extern keyboard_irq]
[global keyboard_isr]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void keyboard_isr()
;
; This is the keyboard Interrupt Service Routine that is invoked
; whenever an irq is fired on line 6.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

keyboard_isr:
	; Store state
	cld
	pushad
	push ds
	push es
	push fs
	push gs

	;call the floppy handler
	call keyboard_irq

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
