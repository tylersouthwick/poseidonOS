#makefile to compile stage2.bin and kernel.bin
include rules.mk

KERNEL_OBJS = kernel_wrapper.o kernel.o 

KERNEL_STATIC_LIBS=interrupts/interrupts.a multitasking/multitasking.a mm/mm.a \
		screen/screen.o string/string.a bios.o dma.o \
		devices/manager/devicemanager.a drivers.o devices/floppy/floppy.a \
		exec/exec.a vfs/vfs.a fat/fat.a util/util.a

compile:
	cd interrupts; make
	cd mm; make
	cd multitasking; make
	cd screen; make
	cd string; make
	cd devices/manager; make
	cd devices/floppy; make
	cd fat; make
	cd vfs; make
	cd util; make
	cd exec; make
	make kernel.elf

######################################Kernel###############################
kernel_wrapper.o : kernel_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o $@ $<

exec_wrapper.o : exec_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o $@ $<

kernel.o  : kernel.c ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h
drivers.o : drivers.c ${KERNEL_INCLUDE}/drivers.h ${KERNEL_INCLUDE}/ktypes.h
dma.o	  	: dma.c ${KERNEL_INCLUDE}/dma.h 
bios.o	  : bios.c ${KERNEL_INCLUDE}/bios.h
mount.o	  : mount.c ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h
exec.o	  : exec.c ${KERNEL_INCLUDE}/kernel.h ${KERNEL_INCLUDE}/ktypes.h ${KERNEL_INCLUDE}/kdebug.h

###########################################################################

####################################System################################3

#link and build kernel.bin
kernel.elf: ${KERNEL_OBJS} $(KERNEL_STATIC_LIBS)
	$(LD) $(LDFLAGS) -o kernel.elf $(KERNEL_OBJS) $(KERNEL_STATIC_LIBS) string/string.o

clean:
	cd interrupts; make clean
	cd mm; make clean
	cd multitasking; make clean
	cd screen; make clean
	cd string; make clean
	cd devices/manager; make clean
	cd fat; make clean
	cd devices/floppy; make clean
	cd vfs; make clean
	cd util; make clean
	rm -f *.o
	rm -f kernel.elf
