#makefile to compile the fat12 fs driver
include ../rules.mk

FAT_OBJS = fat.o file.o directory.o 

default: fat.a

#################################compile stuff###############################
fat.o : fat.c ../include/fat.h ../include/vfs.h
file.o : file.c ../include/fat.h 
directory.o : directory.c ../include/fat.h 
######################################floppy.a###############################
fat.a: $(FAT_OBJS)
	$(AR) $(ARFLAGS) fat.a $(FAT_OBJS)

clean:
	rm -f fat.a
	rm -f fat.o
	rm -f file.o
	rm -f directory.o
###########################################################################
