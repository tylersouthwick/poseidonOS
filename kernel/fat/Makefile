#makefile to compile the fat12 fs driver
include ../rules.mk

FAT_OBJS = fat.o open.o read.o write.o

default: fat.a

#################################compile stuff###############################
fat.o : fat.c ../include/fat.h ../include/vfs.h
open.o : open.c ../include/fat.h 
read.o : read.c ../include/fat.h 
write.o : write.c ../include/fat.h 
######################################floppy.a###############################
fat.a: $(FAT_OBJS)
	$(AR) $(ARFLAGS) fat.a $(FAT_OBJS)

clean:
	rm -f fat.a
	rm -f fat.o
	rm -f open.o
	rm -f read.o
	rm -f write.o
###########################################################################
