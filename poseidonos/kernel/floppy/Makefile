#makefile to compile the floppy tatic library
include ../rules.mk

FLOPPY_OBJS = floppy.o floppy_wrapper.o

default: floppy.a

#################################compile stuff###############################
floppy.o : floppy.c ../include/floppy.h ../include/bios.h
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
