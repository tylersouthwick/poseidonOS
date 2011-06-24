KERNEL_FILE=poseidon.sys
LIBRARIES = core screen multitasking util mm

########################################3
AS=nasm
AS_FORMAT=elf
CC=gcc
AR=ar
ARFLAGS=-rs
ARCH=i586

.PHONY: $(LIBRARIES) default clean image

default : $(KERNEL_FILE)

LIBS = $(addsuffix /lib.ar,$(LIBRARIES))

$(KERNEL_FILE) : $(LIBRARIES) kernel.ld
	@echo "(LD) ${KERNEL_FILE}"
	@ld -melf_i386 -T kernel.ld -o ${KERNEL_FILE} --start-group $(LIBS) --end-group
	@echo "Sanity Check"
	@mbchk ${KERNEL_FILE}

#################
## libraries
#################
$(LIBRARIES):
	@echo "(MAKE) $@"
	@make -C $@

clean : ${CLEAN_LIBRARIES}
	@rm -f ${KERNEL_FILE}
	@for d in $(LIBRARIES); do make -C $$d clean; done

