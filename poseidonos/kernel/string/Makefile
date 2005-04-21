#makefile to compile string.a
include ../rules.mk

STRING_OBJS = string.o string_assembly.o 

compile: string.a

############################################compile stuff#####################################
string.o : string.c ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

string_assembly.o : string.asm
	$(AS) -f ${AS_FORMAT} -o string_assembly.o string.asm
##############################################################################################

string.a : ${STRING_OBJS}
	$(AR) $(ARFLAGS) string.a $(STRING_OBJS)
	
clean:
	rm -f string_assembly.o
	rm -f string.o
	rm -f string.a
