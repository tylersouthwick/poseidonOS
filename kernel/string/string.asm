;  File: string.asm
;   Description: provides basic memory and string operations

;function: void *memcpy(void *dest, void *src, size_t n);
;<description>copy n bytes from src to dest</description>
[global memcpy]
%define dest ebp+8
%define src ebp+12
%define n ebp+16
memcpy:
	push ebp
	mov ebp, esp

	mov esi, [src]
	mov edi, [dest]
	mov ecx, [n]
	rep movsb
	pop ebp
	ret
;function: void *memmove(void *dest, void *src, size_t n);
;<description>copy n bytes from src to dest, guarenteeing correct behavior for overlapping strings</description>
;<note>this will eventually be it's own function</note>
[global memmove]
memmove:
	jmp memcpy;

;Function: void *memccpy(void *dest, void *src, int c, size_t n);
;<description>copy no more than n bytes of src to dest, stopping when c is found
;return the position in dest one byte past where C was copied,
;or NULL if C was not found in the first N bytes of src.</description>
%define dest ebp+8
%define src ebp+12
%define c ebp+16
%define n ebp+20
[global memccpy]
memccpy:
	push ebp
	mov ebp, esp
	;first find where c occurs
	mov al, [c]
	mov edi, [src]
	or ecx, ecx
	mov ecx, [n]
	repne scasb
	;was c found?
	jg .error	;no (ZF=0)
	;else
	mov esi, [src]
	mov edi, [dest]
	mov eax, [n]
	sub eax, ecx
	mov ecx, eax
	rep movsb
	jmp .done
	.error:
		mov eax, 0
	.done:
		pop ebp
		ret
;function:void memset(void *s, int c, size_t n);
;<description>set n bytes of s to c</description>
%define s ebp+8
%define c ebp+12
%define n ebp+16
[global memset]
memset:
	push ebp
	mov ebp, esp
	mov al, [c]
	mov ecx, [n]
	mov edi, [s]
	rep stosb
	pop ebp
	ret


;compare n bytes of s1 and s2
;int memcmp(void *s1, void *s2, size_t n);
%define s1 ebp+8
%define s2 ebp+12
%define n ebp+16
[global memcmp]
memcmp:
	push ebp
	mov ebp, esp
	mov edi, [s1]
	mov esi, [s2]
	mov ecx, [n]
	repe cmpsb
	;are they different?
	cmp ecx, 0
	je .no_difference ;no
	;else
	mov eax, [n]
	sub eax, ecx
	jmp .done
	.no_difference:
		mov eax, 0
	.done:
		pop ebp
		ret
	
;search n bytes of s for c
;void *memchr (void *s, int c, size_t n);

;copy src to dest
;char *strcpy(char *dest, char *src);
%define dest ebp+8
%define src ebp+12
[global strcpy]
strcpy:
	push ebp
	mov ebp, esp
	;find length of string
	mov edi, [src]
	mov ecx, 0xFFFFFFFF	;this allows for a *VERY* large string
	mov al, 0
	repne scasb
	mov eax, 0xFFFFFFFF
	sub eax, ecx
	xchg eax, ecx
	;size of string is now in ecx
	mov esi, [src]
	mov edi, [dest]
	rep movsb
	pop ebp
	ret
;copy no more than N characters of src to dest
;char *strncpy (char *dest, char *src, size_t n);
;NOT TESTED!
%define dest ebp+8
%define src ebp+12
%define n ebp+16
[global strncpy]
strncpy:
	push ebp
	mov ebp, esp
	;find length of string
	mov edi, [src]
	mov ecx, 0xFFFFFFFF	;this allows for a *VERY* large string
	mov al, 0
	repne scasb
	mov eax, 0xFFFFFFFF
	sub eax, ecx
	xchg eax, ecx
	;size of string is now in ecx
	;is n > ecx?
	cmp ecx, [n]
	ja .whole_string
	mov esi, [src]
	mov edi, [dest]
	mov ecx, [n]
	rep movsb
	jmp .done
	.whole_string:
		mov esi, [src]
		mov edi, [dest]
		rep movsb
	.done:
	pop ebp
	ret
;concantinate src onto dest
;char *strcat(char *dest, char *src);
%define dest ebp+8
%define src ebp+12
[global strcat]
strcat:
	push ebp
	mov ebp, esp
	;need memory manager
	pop ebp
	ret
;append no more than n characters from src onto dest
;char *strncat(char *dest, char *src, size_t n);

;compare s1 and s2
;int strcmp(char *s1, char *s2);

;compare n characters of s1 and s2
;int strncmp(char *s1, char *s2, size_t n);