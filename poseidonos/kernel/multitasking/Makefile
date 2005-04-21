#PoseidonOS v.1
#makefile to compile multitasking.a

include ../rules.mk

MULTITASKING_OBJS = multitasking.o scheduler.o scheduler_wrapper.o sleep.o pit.o

compile: multitasking.a

####################################Compile stuff##########################
multitasking.o	: multitasking.c	../include/scheduler.h ../include/tasks.h ../include/irq.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
scheduler.o 		: scheduler.c			../include/scheduler.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
sleep.o					: sleep.c					${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
pit.o						: pit.c						${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

scheduler_wrapper.o : scheduler.asm
	$(AS) -f ${AS_FORMAT} -o scheduler_wrapper.o scheduler.asm
	
###########################################################################

#staticly link multitasking.a
multitasking.a: $(MULTITASKING_OBJS)
	$(AR) $(ARFLAGS) multitasking.a $(MULTITASKING_OBJS)

clean:
	rm -f *.o
	rm -f multitasking.a

