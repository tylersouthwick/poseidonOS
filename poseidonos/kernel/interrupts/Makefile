#makefile to compile idt.a
include ../rules.mk

IDT_OBJS = idt.o int.o int_wrapper.o

compile: interrupts.a

##############################################compile stuff##############################
idt.o : idt.c ../include/idt.h ../include/interrupt.h ../include/irq.h kernel.h ktypes.h kdebug.h
int.o : int.c ../include/paging.h ../include/interrupt.h kernel.h ktypes.h kdebug.h

int_wrapper.o : int_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o int_wrapper.o int_wrapper.asm
#########################################################################################

#build idt.a
interrupts.a : $(IDT_OBJS)
	$(AR) $(ARFLAGS) interrupts.a $(IDT_OBJS)

clean:
	rm -f *.o
	rm -f interrupts.a
