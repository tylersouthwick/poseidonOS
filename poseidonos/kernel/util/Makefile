#makefile to compile util.a
#this creates a library full of data structures and other utilities
#that are needed by the kernel

include ../rules.mk

UTIL_OBJS = map.o

compile: util.a

###########################hashmap stuff###################################
map.o : map.c include/map.h kernel.h kutil.h ktypes.h kdebug.h
###########################################################################

#link util.a
util.a: $(UTIL_OBJS)
	$(AR) $(ARFLAGS) util.a $(UTIL_OBJS)

clean:
	rm -f *.o
	rm -f util.a
