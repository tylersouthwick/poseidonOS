#makefile to compile mm.a
include ../rules.mk

MM_OBJS = mm.o paging.o paging_wrapper.o physical_mem.o sbrk.o virtual_mem.o kmalloc.o

default: mm.a

#############################compile stuff#################################
mm.o : mm.c ../include/mm.h ../include/paging.h ../include/multiboot.h
paging.o : paging.c ../include/mm.h ../include/paging.h
physical_mem.o : physical_mem.c ../include/mm.h ../include/physical_mem.h
sbrk.o : sbrk.c ../include/mm.h ../include/sbrk.h
virtual_mem.o : virtual_mem.c ../include/mm.h ../include/physical_mem.h ../include/virtual_mem.h
kmalloc.o : kmalloc.c ../include/mm.h ../include/sbrk.h ../include/kmalloc.h

paging_wrapper.o : paging_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o $@ $<
###########################################################################

#link and build kernel.bin
mm.a: $(MM_OBJS)
	$(AR) $(ARFLAGS) mm.a $(MM_OBJS)

clean:
	rm -f *.o
	rm -f mm.a
