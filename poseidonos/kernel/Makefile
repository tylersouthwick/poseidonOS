KERNEL_STATIC_LIBS= \
		screen/screen.a \
		devices/manager/devicemanager.a \
		devices/floppy/floppy.a \
		devices/keyboard/keyboard.a \
		mm/mm.a \
		interrupts/interrupts.a \
		multitasking/multitasking.a \
		exec/exec.a \
		vfs/vfs.a \
		fat/fat.a \
		util/util.a \
		string/string.a

KERNEL_OBJS = \
		kernel_wrapper.o \
		kernel.o \
		drivers.o \
		dma.o

compile:
	cd interrupts; make
	cd mm; make
	cd multitasking; make
	cd screen; make
	cd string; make
	cd devices; make
	cd fat; make
	cd vfs; make
	cd util; make
	cd exec; make

####################################System################################3

#link and build kernel.bin
kernel.elf: ${KERNEL_OBJS} $(KERNEL_STATIC_LIBS)
	ld -Tkernel.ld -o kernel.elf $(KERNEL_OBJS) $(KERNEL_STATIC_LIBS) 

clean:
	cd interrupts; make clean
	cd mm; make clean
	cd multitasking; make clean
	cd screen; make clean
	cd string; make clean
	cd devices; make clean
	cd fat; make clean
	cd vfs; make clean
	cd util; make clean
	cd exec; make clean
	rm -f ${C_OBJS} kernel.elf

depclean:
	cd interrupts; make depclean
	cd mm; make depclean
	cd multitasking; make depclean
	cd screen; make depclean
	cd string; make depclean
	cd devices; make depclean
	cd fat; make depclean
	cd vfs; make depclean
	cd util; make depclean
	cd exec; make depclean
	rm -f ${C_OBJS} kernel.elf
