AS=nasm
CC=gcc
AS_FORMAT=elf
HEADER_FILE=../../kernel/include/libc.h
SHARED_CFLAGS=-I${INCLUDE_DIR} -std=c99
# -m32 -march=${ARCH}
KERNEL_CFLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -Wall -Winline -Wmissing-declarations -Wredundant-decls -finline-functions -fpic -fno-leading-underscore $(SHARED_CFLAGS)

OBJS=start.o libc_generated.o screen.o

build : libc.a

clean :
	rm -f *.o
	rm -f *.a
	rm -f *_generated.*

libc.a : ${OBJS}
	ar rcs libc.a ${OBJS}

libc_generated.h : ${HEADER_FILE} generate
	./generate -p > libc_generated.h

libc_generated.asm : ${HEADER_FILE} generate
	./generate -a > libc_generated.asm

screen.c : libc_generated.h libc.h

######
# assembly dependencies
######
%.o : %.asm
	@echo "(ASM) $<"
	@$(AS) -f $(AS_FORMAT) -o $@ $<
######
# c files
######
%.o : %.c
	@echo "(GCC) $<"
	@$(CC) -c $(KERNEL_CFLAGS) -o $@ $<
