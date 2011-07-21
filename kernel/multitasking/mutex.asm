
;void mutex_lock(mutext *mutex);
mutex_lock:
	mov eax, [esp+4] ;the pointer to the mutex structure
	mov ebx, 1
	.loop:
	lock
	cmpxchg 0, ebx
	je .loop
	ret

;void mutex_unlock(mutext *mutex);
mutex_unlock:
	mov eax, [esp+4] ;the pointer to the mutex structure
	mov ebx, 0
	;update to 0 only if it was a 1
	lock
	cmpxchg 1, ebx
	ret
