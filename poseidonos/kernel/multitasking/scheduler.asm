;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PoseidonOS v.1
; File: scheduler.asm
; (c) 2004 Tyler Southwick
; Liscensed under the GPL (checkout README or http://www.gnu.org/licenses/gpl.txt)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[section .text]
										; the current process
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; scheduler_isr
; C-Prototype: void scheduler_isr()
;
; This is the isr for the process scheduler.  It pushes all the registers onto the
; stack of the current process, loads the kernel process, and calls the actual
; scheduler.  The kernel process is then unloaded while the new process is loaded.
; 
; Parameters:
;		none
;	
; Return value:
;		none
;
;	Preconditions:
;		There MUST be a valid pointer to a system process
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[global scheduler_isr]
scheduler_isr:
	; Store state
	cld
	pushad
	push ds
	push es
	push fs
	push gs

	; Store current esp into the current process thread structure
	mov ecx, dword[current_process]
	mov [ecx], esp

	;call the scheduler that will decide what thread to execute next it
	call getCurrentProcess
	
	; Exchange the stack with the new process' stack
	; which is returned in eax by getCurrentProcess
	mov esp, eax;
		
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

; global variables needed by the scheduler
[extern current_process] 				; the pointer to the process_queue
[extern getCurrentProcess]				; method that runs the scheduler and gets
