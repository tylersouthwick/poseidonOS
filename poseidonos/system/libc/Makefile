LIBC_OBJS = stdio_wrapper.o
AS_FORMAT=aout
AS=nasm

default : libc.a

############################################compile stuff#####################################
#string.o : string.c kernel.h ktypes.h kdebug.h

stdio_wrapper.o : stdio.asm
	$(AS) -f ${AS_FORMAT} -o stdio_wrapper.o stdio.asm
##############################################################################################

libc.a : ${LIBC_OBJS}
	$(AR) $(ARFLAGS) libc.a $(STRING_OBJS)
	
clean:
	rm -f *.o
	rm -f *.a
