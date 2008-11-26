KERNEL_FILE=poseidon.sys

KERNEL_STATIC_LIBS= \
		screen/libscreen.a \
		string/libstring.a 

KERNEL_LINKER_LIBS= \
		-lscreen.a 

KERNEL_OBJS = \
		kernel_wrapper.o \
		kernel.o 

compile:
	@$(MAKE) -C screen
	@$(MAKE) -C string
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
	@$(MAKE) -C screen clean
	@$(MAKE) -C string clean
	@echo "(RM) ${KERNEL_OBJS} ${KERNEL_FILE}"
	@rm -f ${KERNEL_OBJS} ${KERNEL_FILE} 

depclean:
	@$(MAKE) -C screen depclean
	@$(MAKE) -C string depclean
	@echo "(RM) ${KERNEL_OBJS} ${KERNEL_FILE}"
	@rm -f ${KERNEL_OBJS} ${KERNEL_FILE} 
	@rm -f kernel.aux kernel.log kernel.pdf
	@rm -f lib.a
