#makefile to compile vfs.a
include ../rules.mk

VFS_OBJS = mount.o ls.o

default: vfs.a

#############################compile stuff#################################
mount.o : mount.c ../include/kmalloc.h ../include/vfs.h ../include/ktypes.h
ls.o : ls.c ../include/kmalloc.h ../include/vfs.h ../include/ktypes.h
###########################################################################

#link and build kernel.bin
vfs.a: $(VFS_OBJS)
	$(AR) $(ARFLAGS) vfs.a $(VFS_OBJS)

clean:
	rm -f ${VFS_OBJS}
	rm -f vfs.a
