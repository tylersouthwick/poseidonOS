default : hello elf
	./elf hello

hello : hello.c
	gcc -m32 hello.c -o hello

elf : elf.c elf.h exec.h
	gcc -m32 elf.c -o elf

clean : 
	rm -f hello elf
