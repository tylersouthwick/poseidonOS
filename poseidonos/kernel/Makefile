#makefile to compile stage2.bin and kernel.bin
include rules.mk

KERNEL_OBJS = kernel_wrapper.o kernel.o exec.o

KERNEL_STATIC_LIBS=interrupts/interrupts.a multitasking/multitasking.a mm/mm.a \
		screen/screen.o string/string.a bios.o dma.o \
		devicemanager/devicemanager.a drivers.o floppy/floppy.a \
		vfs/vfs.a fat/fat.a util/util.a 

compile:
	cd interrupts; make
	cd mm; make
	cd multitasking; make
	cd screen; make
	cd string; make
	cd devicemanager; make
	cd floppy; make
	cd fat; make
	cd vfs; make
	cd util; make
	make kernel.elf

######################################Kernel###############################
kernel_wrapper.o : kernel_wrapper.asm
	$(AS) -f ${AS_FORMAT} -o $@ $<

kernel.o  : kernel.c kernel.h include/ktypes.h
drivers.o : drivers.c include/drivers.h include/ktypes.h
dma.o	  	: dma.c include/dma.h include/bios.h
bios.o	  : bios.c include/bios.h
mount.o	  : mount.c include/mount.h include/floppy.h include/fat.h include/vfs.h
exec.o	  : exec.c kernel.h ktypes.h kdebug.h

###########################################################################

####################################System################################3

#link and build kernel.bin
kernel.elf: kernel_wrapper.o kernel.o $(KERNEL_STATIC_LIBS)
	$(LD) $(LDFLAGS) -o kernel.elf $(KERNEL_OBJS) $(KERNEL_STATIC_LIBS) string/string.o

clean:
	cd interrupts; make clean
	cd mm; make clean
	cd multitasking; make clean
	cd screen; make clean
	cd string; make clean
	cd devicemanager; make clean
	cd fat; make clean
	cd floppy; make clean
	cd vfs; make clean
	cd util; make clean
	rm -f kernel.o
	rm -f kernel_wrapper.o
	rm -f dma.o
	rm -f bios.o
	rm -f mount.o
	rm -f drivers.o
	rm -f kernel.elf
