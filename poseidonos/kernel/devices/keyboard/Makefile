#makefile to compile keyboard.a
include ../../rules.mk

OBJS = keyboard.o keyboard_wrapper.o
LIB_NAME = keyboard.a

compile: ${LIB_NAME} 

#################################compile stuff###############################
keyboard.o : keyboard.c ${KERNEL_INCLUDE}/irq.h ${KERNEL_INCLUDE}/devices/manager.h ${KERNEL_INCLUDE}/devices/keyboard.h ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h 
keyboard_wrapper.o : keyboard_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o keyboard_wrapper.o keyboard_wrapper.asm
######################################floppy.a###############################
${LIB_NAME}: $(OBJS)
	$(AR) $(ARFLAGS) ${LIB_NAME} $(OBJS)

clean:
	rm -f *.o
	rm -f ${LIB_NAME}
###########################################################################
