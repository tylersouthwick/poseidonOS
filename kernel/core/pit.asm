section .bss
system_timer_fractions		resd 1
[global system_timer_ms]
system_timer_ms			resd 1
IRQ0_fractions			resd 1
IRQ0_ms				resd 1
[global IRQ0_frequency]
IRQ0_frequency			resd 1
PIT_reload_value		resw 1

section .text
[global pit_init]
pit_init:
	pushad
	mov ebx, 8000
	call initPIT
	popad
	ret

;Input
;  Shamelessly copied from http://wiki.osdev.org/PIT
;  ebx  Desired PIT frequency in Hz
initPIT:
	pushad

	; Do some checking
	mov eax, 0x10000	;eax = reload value for slowest possible frequency
	cmp ebx,18		;Is the requested frequency too loow
	jbe .gotReloadValue	; yes, use slowest possible frequency

	mov eax,1		;ax = reload value for fastest ossible frequency
	cmp ebx, 1193181	;Is the requested frequency too high?
	jae .gotReloadValue	;yes, use fastest possible frequency

	; Calculate the reload value
	mov eax, 3579545
	mov edx,0		;edx:eax = 3579545
	div ebx			;eax = 3579545 / frequency, edx = remainder
	cmp edx, 3579545/2	;Is the remainder more than half?
	jb .l1			;no round down
	inc eax			;yes, round up

.l1:
	mov ebx, 3
	mov edx, 0		;edx:eax = 3579545 * 256 / frequency
	div ebx			;eax = (3579545 * 256 / 3 * 256) / frequency
	cmp edx, 3/2		;Is the remainder more than half?
	jb .l2			;no, round down
	inc eax			;yes, round up
.l2:

	;store the reload value and calculate the actual frequency
.gotReloadValue:
	push eax		;Store reload_value for later
	mov [PIT_reload_value], ax	;Store reload_value for later
	mov ebx, eax		;ebx = reload value

	mov eax, 3579545
	mov edx, 0
	div ebx			;eax = 3579545 / reload_value, edx = remainder
	cmp edx, 3579545 / 2	;is the remainder more than half?
	jb .l3			; no, round down
	inc eax			; yes, round up
.l3:
	mov ebx, 3
	mov edx, 0		;edx:eax = 3579545 / reload_value
	div ebx			;eax = (35679545 / 3) / frequency
	cmp edx, 3/2		;is the remainder more than half?
	jb .l4			;no round down
	inc eax			;yes round up
.l4:
	mov [IRQ0_frequency], eax	;store the actual frequency for displaying later

	pop ebx			;ebx = reload_value
	mov eax, 0xDBB3A062	;eax = 3000 * (2^42) /3579545
	mul ebx			;edx:eax = reload value * 3000 * (2^42) /3579545
	shrd eax, edx, 10
	shr edx, 10		;edx:eax = reload value * 3000 * (2^42) /3579545 / (2^10)
	mov [IRQ0_ms], edx	;set the whol ms between IRQs
	mov [IRQ0_fractions], eax	;set fractions of 1 ms between IRQs

	;Program the PIT channel
	pushfd
	cli			;disabled interrupts

	mov al, 00110100b	;channel 0, lobyte/hibyte, rate generator
	out 0x43, al

	mov ax, [PIT_reload_value]	;ax = 16 bit reload value
	out 0x40, al			;Set low byte of PIT reload value
	mov al, ah		;ax = high 8 bits of reload value
	out 0x40, al		;set high byte of PIT reload value

	popfd

	popad
	ret

[global timer_isr]
timer_isr:
	pusha
	push gs
	push fs
	push ds
	push es
	
	mov eax, [IRQ0_fractions]
	mov ebx, [IRQ0_ms]			;eax.ebx = amount of time between IRQs
	add [system_timer_fractions], eax	;Update system time tick fractions
	adc [system_timer_ms], ebx		;Update system timer tick milli-seconds

	extern timer_interrupt
	call timer_interrupt

	mov al, 0x20
	out 0x20, al				;Send the EOI to the PIC

	pop es
	pop ds
	pop fs
	pop gs
	popa
	iret
