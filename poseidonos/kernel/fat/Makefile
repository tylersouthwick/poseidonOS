#makefile to compile the fat12 fs driver
include ../rules.mk

FAT_OBJS = fat.o file.o directory.o 

compile: fat.a

#################################compile stuff###############################
fat.o : fat.c 						../include/fat.h ../include/devices.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
file.o : file.c						../include/fat.h ../include/devices.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
directory.o : directory.c ../include/fat.h ../include/devices.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
######################################floppy.a###############################
fat.a: $(FAT_OBJS)
	$(AR) $(ARFLAGS) fat.a $(FAT_OBJS)

clean:
	rm -f fat.a
	rm -f fat.o
	rm -f file.o
	rm -f directory.o
###########################################################################
