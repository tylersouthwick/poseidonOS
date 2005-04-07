[global printf]
printf:
	mov ebx, 0x0
	int 45h
	ret

[global fopen]
fopen:
	mov ebx, 0x1
	int 45h
	ret

[global fclose]
fclose:
	mov ebx, 0x2
	int 45h
	ret
