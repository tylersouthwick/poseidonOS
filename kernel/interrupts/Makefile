#makefile to compile idt.a
include ../rules.mk

IDT_OBJS = idt.o int.o int_wrapper.o

default: interrupts.a

idt.o : idt.c ${KERNEL_ROOT}/include/idt.h ${KERNEL_ROOT}/include/interrupt.h ${KERNEL_ROOT}/include/ktypes.h

int.o : int.c ${KERNEL_ROOT}/include/idt.h ${KERNEL_ROOT}/include/interrupt.h ${KERNEL_ROOT}/include/ktypes.h ${KERNEL_ROOT}/include/mm.h

int_wrapper.o : int_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o int_wrapper.o int_wrapper.asm

#build idt.a
interrupts.a : $(IDT_OBJS)
	$(AR) $(ARFLAGS) interrupts.a $(IDT_OBJS)

clean:
	rm -f *.o
	rm -f interrupts.a
