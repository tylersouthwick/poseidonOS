#PoseidonOS v.1
#makefile to compile multitasking.a

include ../rules.mk

MULTITASKING_OBJS = multitasking.o scheduler.o scheduler_wrapper.o sleep.o pit.o

compile: multitasking.a

####################################Compile stuff##########################
multitasking.o	: multitasking.c	../include/scheduler.h ../include/tasks.h ../include/irq.h kernel.h ktypes.h kdebug.h
scheduler.o 		: scheduler.c			../include/scheduler.h kernel.h ktypes.h kdebug.h
sleep.o					: sleep.c					kernel.h ktypes.h kdebug.h
pit.o						: pit.c						kernel.h ktypes.h kdebug.h

scheduler_wrapper.o : scheduler.asm
	$(AS) -f ${AS_FORMAT} -o scheduler_wrapper.o scheduler.asm
	
###########################################################################

#staticly link multitasking.a
multitasking.a: $(MULTITASKING_OBJS)
	$(AR) $(ARFLAGS) multitasking.a $(MULTITASKING_OBJS)

clean:
	rm -f *.o
	rm -f multitasking.a

