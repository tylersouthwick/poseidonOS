#makefile to compile devicemanager.a

include ../rules.mk

UTIL_OBJS = hashmap/HashMap.o

default: util.a

#############################compile stuff#################################
#.o : devicemanager.c ../include/devicemanager.h ../include/ktypes.h ../include/kmalloc.h ../include/screen.h
###########################################################################

###########################hashmap stuff###################################
hashmap/HashMap.o : hashmap/HashMap.c include/HashMap.h
###########################################################################

#link and build kernel.bin
util.a: $(UTIL_OBJS)
	$(AR) $(ARFLAGS) util.a $(UTIL_OBJS)

clean:
	rm -f hashmap/*.o
	rm -f util.a
