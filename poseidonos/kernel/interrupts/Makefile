#makefile to compile idt.a
include ../rules.mk

IDT_OBJS = idt.o int.o int_wrapper.o user.o

compile: interrupts.a

##############################################compile stuff##############################
int.o		: int.c		${KERNEL_INCLUDE}/mm/paging.h ${KERNEL_INCLUDE}/interrupt.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
user.o	: user.c	${KERNEL_INCLUDE}/interrupt.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

idt.o		: idt.c		${KERNEL_INCLUDE}/idt.h ${KERNEL_INCLUDE}/interrupt.h ${KERNEL_INCLUDE}/irq.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

int_wrapper.o : int_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o int_wrapper.o int_wrapper.asm
#########################################################################################

#build idt.a
interrupts.a : $(IDT_OBJS)
	$(AR) $(ARFLAGS) interrupts.a $(IDT_OBJS)

clean:
	rm -f *.o
	rm -f interrupts.a
