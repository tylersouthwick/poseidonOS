#makefile to compile util.a
#this creates a library full of data structures and other utilities
#that are needed by the kernel

include ../rules.mk

UTIL_OBJS = map.o stack.o md5.o

compile: util.a

###########################hashmap stuff###################################
map.o   : map.c   ${KERNEL_INCLUDE}/util/map.h ${KERNEL_INCLUDE}/kdebug.h
stack.o : stack.c ${KERNEL_INCLUDE}/util/stack.h ${KERNEL_INCLUDE}/kdebug.h
md5.o   : md5.c   ${KERNEL_INCLUDE}/util/md5.h ${KERNEL_INCLUDE}/kdebug.h
###########################################################################

#link util.a
util.a: $(UTIL_OBJS)
	$(AR) $(ARFLAGS) util.a $(UTIL_OBJS)

clean:
	rm -f *.o
	rm -f util.a
