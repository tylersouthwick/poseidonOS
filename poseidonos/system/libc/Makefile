LIBC_OBJS = stdio_wrapper.o
AS_FORMAT=aout
AS=nasm

default : libc.a

############################################compile stuff#####################################
#string.o : string.c kernel.h ktypes.h kdebug.h

stdio_wrapper.o : stdio.asm
	@echo "(AS) stdio.asm"
	@$(AS) -f ${AS_FORMAT} -o stdio_wrapper.o stdio.asm
##############################################################################################

libc.a : ${LIBC_OBJS}
	@echo "(AR) libc.a"
	$(AR) $(ARFLAGS) libc.a $(STRING_OBJS)
	
clean:
	@echo "rm stdio_wrapper.o libc.a"
	rm -f stdio_wrapper.o libc.a
