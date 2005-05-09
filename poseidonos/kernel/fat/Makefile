#makefile to compile the fat12 fs driver
include ../rules.mk

FAT_OBJS = fat.o file.o directory.o 

compile: fat.a

#################################compile stuff###############################
fat.o : fat.c 						${KERNEL_INCLUDE}/fat.h ${KERNEL_INCLUDE}/vfs.h ${KERNEL_INCLUDE}/devices/floppy.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
file.o : file.c						${KERNEL_INCLUDE}/fat.h ${KERNEL_INCLUDE}/vfs.h ${KERNEL_INCLUDE}/devices/floppy.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
directory.o : directory.c ${KERNEL_INCLUDE}/fat.h ${KERNEL_INCLUDE}/vfs.h ${KERNEL_INCLUDE}/devices/floppy.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
######################################floppy.a###############################
fat.a: $(FAT_OBJS)
	$(AR) $(ARFLAGS) fat.a $(FAT_OBJS)

clean:
	rm -f fat.a
	rm -f fat.o
	rm -f file.o
	rm -f directory.o
###########################################################################
