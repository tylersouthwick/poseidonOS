#makefile to compile vfs.a
include ../rules.mk

VFS_OBJS = mount.o ls.o file.o

compile: vfs.a

#############################compile stuff#################################
mount.o : mount.c		${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h ../include/fat.h
file.o : file.c			${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h ../include/fat.h
ls.o : ls.c					${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
###########################################################################

#link and build kernel.bin
vfs.a: $(VFS_OBJS)
	$(AR) $(ARFLAGS) vfs.a $(VFS_OBJS)

clean:
	rm -f ${VFS_OBJS}
	rm -f vfs.a
