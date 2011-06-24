KERNEL_FILE=poseidon.sys
LIBRARIES = core screen multitasking util mm

########################################3
AS=nasm
AS_FORMAT=elf
CC=gcc
AR=ar
ARFLAGS=-rs
ARCH=i586

default : $(KERNEL_FILE)

LIBS = $(addsuffix /lib.ar,$(LIBRARIES))

$(KERNEL_FILE) : libraries kernel.ld ${KERNEL_OBJS}
	@echo "(LD) ${KERNEL_FILE}"
	@ld -melf_i386 -T kernel.ld -o ${KERNEL_FILE} --start-group $(LIBS) --end-group
	@echo "Sanity Check"
	@mbchk ${KERNEL_FILE}

#################
## libraries
#################
LIBS = $(addsuffix /lib.ar,$(LIBRARIES))
libraries : $(LIBS)
%/lib.ar : %
	@echo "(MAKE) $<"
	@make -C $<

%/lib.ar.clean : %
	@echo "(Clean) $<"
	@make -C $< clean

CLEAN_LIBRARIES=$(subst .ar,.ar.clean,$(LIBS))
clean : ${CLEAN_LIBRARIES}
	@rm -f ${KERNEL_FILE}

image : package
	@cd build-tools; ./create_image --clean -f PoseidonOS.img
	@cd build-tools; ./create_image --create -f PoseidonOS.img
	@mv build-tools/PoseidonOS.img .

