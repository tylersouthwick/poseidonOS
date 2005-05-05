#makefile to compile mm.a
include ../rules.mk

MM_OBJS = mm.o paging.o paging_wrapper.o physical_mem.o sbrk.o virtual_mem.o kmalloc.o

compile: mm.a

#############################compile stuff#################################
mm.o : mm.c 										${KERNEL_INCLUDE}/mm/paging.h ${KERNEL_INCLUDE}/mm/multiboot.h ${KERNEL_INCLUDE}/mm/sbrk.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
paging.o : paging.c 						${KERNEL_INCLUDE}/mm/paging.h ${KERNEL_INCLUDE}/mm/physical_mem.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
physical_mem.o : physical_mem.c ${KERNEL_INCLUDE}/mm/physical_mem.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
sbrk.o : sbrk.c 								${KERNEL_INCLUDE}/mm/mm.h ${KERNEL_INCLUDE}/mm/sbrk.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
virtual_mem.o : virtual_mem.c 	${KERNEL_INCLUDE}/mm/physical_mem.h ${KERNEL_INCLUDE}/mm/virtual_mem.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
kmalloc.o : kmalloc.c 					${KERNEL_INCLUDE}/mm/sbrk.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

paging_wrapper.o : paging_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o $@ $<
###########################################################################

#link and build kernel.bin
mm.a: $(MM_OBJS)
	$(AR) $(ARFLAGS) mm.a $(MM_OBJS)

clean:
	rm -f *.o
	rm -f mm.a
