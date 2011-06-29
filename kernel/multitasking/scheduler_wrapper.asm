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
%include "multitasking.mac"
[global scheduler_isr]
scheduler_isr:
  REG_SAVE
	;call the scheduler that will decide what thread to execute next it
	call schedule
  REG_RESTORE

; global variables needed by the scheduler
[extern current_process] 				; the pointer to the process_queue
[extern schedule]		; fuction that runs the scheduler and gets
