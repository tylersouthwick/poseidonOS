#makefile to compile devicemanager.a

include ../rules.mk

DEVICEMANAGER_OBJS = devicemanager.o

compile: devicemanager.a

#############################compile stuff#################################
devicemanager.o : devicemanager.c ../include/devicemanager.h kernel.h kutil.h kdebug.h
###########################################################################

#link and build kernel.bin
devicemanager.a: $(DEVICEMANAGER_OBJS)
	$(AR) $(ARFLAGS) devicemanager.a $(DEVICEMANAGER_OBJS)

clean:
	rm -f *.o
	rm -f devicemanager.a
