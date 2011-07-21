
;void mutex_lock(mutext *mutex);
[global mutex_lock]
mutex_lock:
	push ebx
	mov ebx, [esp+8] ;the pointer to the mutex structure
	pushad
.loop:
	mov eax, 0
	mov ecx, 1
	lock
	cmpxchg [ebx], ecx
	jne .loop
	popad
	pop ebx
	ret

;void mutex_unlock(mutext *mutex);
[global mutex_unlock]
mutex_unlock:
	push ebx
	mov ebx, [esp+8] ;the pointer to the mutex structure
	pushad
	mov eax, 1
	mov ecx, 0
	.loop:
	lock
	cmpxchg [ebx], ecx
	je .loop
	popad
	pop ebx
	ret
	ret
