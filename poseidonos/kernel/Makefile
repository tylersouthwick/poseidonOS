KERNEL_FILE=poseidon.sys
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
	@$(MAKE) -C interrupts
	@$(MAKE) -C mm
	@$(MAKE) -C multitasking
	@$(MAKE) -C screen
	@$(MAKE) -C string
	@$(MAKE) -C devices
	@$(MAKE) -C fs
	@$(MAKE) -C util
	@$(MAKE) -C exec
	@$(MAKE) ${KERNEL_FILE}

####################################System################################3
KERNEL_TOP="y"
include kernel.mk

#link and build kernel.bin
${KERNEL_FILE}: ${KERNEL_OBJS} $(KERNEL_STATIC_LIBS)
	@echo "(LD) ${KERNEL_FILE}"
	@ld -Tkernel.ld -o ${KERNEL_FILE} $(KERNEL_OBJS) $(KERNEL_STATIC_LIBS) 
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
