#PoseidonOS v.1
#makefile to compile multitasking.a

include ../rules.mk

MULTITASKING_OBJS = multitasking.o scheduler.o scheduler_wrapper.o sleep.o pit.o

default: multitasking.a

####################################Compile stuff##########################
multitasking.o	: multitasking.c ../include/multitasking.h ../include/mm.h ../include/kmalloc.h
scheduler.o 		: scheduler.c ../include/multitasking.h ../include/mm.h ../include/kmalloc.h
sleep.o					: sleep.c ../include/multitasking.h
pit.o						: pit.c ../include/bios.h

scheduler_wrapper.o : scheduler.asm
	$(AS) -f ${AS_FORMAT} -o scheduler_wrapper.o scheduler.asm
	
###########################################################################

#staticly link multitasking.a
multitasking.a: $(MULTITASKING_OBJS)
	$(AR) $(ARFLAGS) multitasking.a $(MULTITASKING_OBJS)

clean:
	rm -f *.o
	rm -f multitasking.a

