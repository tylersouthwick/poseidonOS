#makefile to compile the floppy static library
include ../rules.mk

FLOPPY_OBJS = floppy.o floppy_wrapper.o

compile: floppy.a

#################################compile stuff###############################
floppy.o : floppy.c ../include/irq.h devices.h kernel.h ktypes.h kdebug.h 
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
