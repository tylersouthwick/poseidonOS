#makefile to compile the floppy static library
include ../../rules.mk

FLOPPY_OBJS = floppy.o floppy_wrapper.o

compile: floppy.a

#################################compile stuff###############################
floppy.o : floppy.c ${KERNEL_INCLUDE}/irq.h ${KERNEL_INCLUDE}/devices/floppy.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h 
floppy_wrapper.o : floppy.asm
	$(AS) -f ${AS_FORMAT} -o floppy_wrapper.o floppy.asm
######################################floppy.a###############################
floppy.a: $(FLOPPY_OBJS)
	$(AR) $(ARFLAGS) floppy.a $(FLOPPY_OBJS)

clean:
	rm -f floppy.a
	rm -f floppy.o
	rm -f floppy_wrapper.o
###########################################################################
