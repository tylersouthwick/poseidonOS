#makefile to compile devicemanager.a

include ../rules.mk

DEVICEMANAGER_OBJS = devicemanager.o

default: devicemanager.a

#############################compile stuff#################################
devicemanager.o : devicemanager.c ../include/devicemanager.h ../include/ktypes.h ../include/kmalloc.h ../include/screen.h
###########################################################################

#link and build kernel.bin
devicemanager.a: $(DEVICEMANAGER_OBJS)
	$(AR) $(ARFLAGS) devicemanager.a $(DEVICEMANAGER_OBJS)

clean:
	rm -f *.o
	rm -f devicemanager.a
