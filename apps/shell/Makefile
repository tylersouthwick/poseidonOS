build: shell.app

INCLUDE_DIR=../libc
SHARED_CFLAGS=-I${INCLUDE_DIR} -std=c99
# -m32 -march=${ARCH}
KERNEL_CFLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -Wall -Winline -Wmissing-declarations -Wredundant-decls -finline-functions -fpic -fno-leading-underscore $(SHARED_CFLAGS)

shell.app : shell.o ../libc/libc.a
	ld -melf_i386 -o shell.app shell.o ../libc/libc.a

shell.o : ../libc/libc.h

######
# cpp files
######
%.o : %.c
	@echo "(GCC) $<"
	@$(CC) -c $(KERNEL_CFLAGS) -o $@ $<

clean :
	rm -f *.o
	rm -f shell.app
