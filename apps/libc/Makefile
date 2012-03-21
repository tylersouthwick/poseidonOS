AS=nasm
AS_FORMAT=elf
HEADER_FILE=../../kernel/include/libc.h

ASM_OBJS=libc.o start.o

build : libc.h libc.a

clean :
	rm -f *.o
	rm -f *.a

libc.a : ${ASM_OBJS}
	ar rcs libc.a ${ASM_OBJS}

libc.h : ${HEADER_FILE} generate
	./generate -p > libc.h

libc.asm : ${HEADER_FILE} generate
	./generate -a > libc.asm

######
# assembly dependencies
######
%.o : %.asm
	@echo "(ASM) $<"
	@$(AS) -f $(AS_FORMAT) -o $@ $<
