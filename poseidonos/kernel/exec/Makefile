#makefile to compile exec.a
include ../rules.mk

EXEC_OBJS=exec_wrapper.o exec.o

compile : exec.a

#############################compile stuff#################################
exec.o : exec.c 					${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h ../include/interrupt.h

exec_wrapper.o : exec_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o $@ $<
###########################################################################

exec.a : ${EXEC_OBJS}
	${AR} ${ARFLAGS} exec.a ${EXEC_OBJS}
