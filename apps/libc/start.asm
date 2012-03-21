global _start
extern main

_start:
	push 0
	push 0
	call main
.end: jmp .end
	
