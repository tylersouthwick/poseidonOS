#makefile to compile idt.a
include ../rules.mk

IDT_OBJS = idt.o int.o int_wrapper.o user.o
CFLAGS = ${KERNEL_CFLAGS} -O0 ${KERNEL_INCLUDE_DIR}

compile: interrupts.a

##############################################compile stuff##############################
int.o		: int.c		../include/mm/paging.h ../include/interrupt.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
user.o	: user.c	../include/interrupt.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

idt.o		: idt.c		../include/idt.h ../include/interrupt.h ../include/irq.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

int_wrapper.o : int_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o int_wrapper.o int_wrapper.asm
#########################################################################################

#build idt.a
interrupts.a : $(IDT_OBJS)
	$(AR) $(ARFLAGS) interrupts.a $(IDT_OBJS)

clean:
	rm -f *.o
	rm -f interrupts.a
