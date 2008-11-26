KERNEL_FILE=poseidon.sys

KERNEL_STATIC_LIBS= \
		screen/libscreen.a \
		devices/manager/libdevicemanager.a \
		devices/floppy/libfloppy.a \
		devices/keyboard/libkeyboard.a \
		mm/libmm.a \
		interrupts/libinterrupts.a \
		multitasking/libmultitasking.a \
		exec/libexec.a \
		fs/vfs/libvfs.a \
		fs/fat/libfat.a \
		util/libutil.a \
		string/libstring.a \
		gdt/libgdt.a

KERNEL_LINKER_LIBS= \
		-lscreen.a \
		-ldevices/manager/devicemanager.a \
		-ldevices/floppy/floppy.a \
		-ldevices/keyboard/keyboard.a \
		-lmm/mm.a \
		-linterrupts/interrupts.a \
		-lmultitasking/multitasking.a \
		-lexec/exec.a \
		-lfs/vfs/vfs.a \
		-lfs/fat/fat.a \
		-lutil/util.a \
		-lstring/string.a \
		-lgdt/gdt.a

KERNEL_OBJS = \
		kernel_wrapper.o \
		kernel.o \
		drivers.o \
		dma.o

compile:
	@$(MAKE) -C interrupts
	@$(MAKE) -C mm
	@$(MAKE) -C multitasking
	@$(MAKE) -C screen
	@$(MAKE) -C string
	@$(MAKE) -C devices
	@$(MAKE) -C fs
	@$(MAKE) -C util
	@$(MAKE) -C exec
	@$(MAKE) -C gdt
	@$(MAKE) ${KERNEL_FILE}

####################################System################################3
KERNEL_TOP="y"
include kernel.mk

#link and build kernel.bin
${KERNEL_FILE}: kernel.ld ${KERNEL_OBJS} $(KERNEL_STATIC_LIBS)
	@echo "(LD) ${KERNEL_FILE}"
	@ld -melf_i386 -Tkernel.ld -o ${KERNEL_FILE} $(KERNEL_OBJS) --start-group $(KERNEL_STATIC_LIBS) --end-group
	@echo
	@echo "####################################"
	@echo "The PoseidonOS kernel has now been built at ${KERNEL_FILE}"
	@echo "####################################"
	@echo

clean:
	@$(MAKE) -C interrupts clean
	@$(MAKE) -C mm clean
	@$(MAKE) -C multitasking clean
	@$(MAKE) -C screen clean
	@$(MAKE) -C string clean
	@$(MAKE) -C devices clean
	@$(MAKE) -C fs clean
	@$(MAKE) -C util clean
	@$(MAKE) -C exec clean
	@echo "(RM) ${KERNEL_OBJS} ${KERNEL_FILE}"
	@rm -f ${KERNEL_OBJS} ${KERNEL_FILE} 

depclean:
	@$(MAKE) -C interrupts depclean
	@$(MAKE) -C mm depclean
	@$(MAKE) -C multitasking depclean
	@$(MAKE) -C screen depclean
	@$(MAKE) -C string depclean
	@$(MAKE) -C devices depclean
	@$(MAKE) -C fs depclean
	@$(MAKE) -C util depclean
	@$(MAKE) -C exec depclean
	@echo "(RM) ${KERNEL_OBJS} ${KERNEL_FILE}"
	@rm -f ${KERNEL_OBJS} ${KERNEL_FILE} 
	@rm -f kernel.aux kernel.log kernel.pdf
	@rm -f lib.a
