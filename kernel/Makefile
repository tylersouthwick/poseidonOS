KERNEL_FILE=poseidon.sys

CORE_OBJS=core/loader.o core/kernel.o 
SCREEN_OBJS=screen/screen.o screen/screen_write.o screen/kprintf.o
UTIL_OBJS=util/string.o util/string_wrapper.o

KERNEL_OBJS=$(CORE_OBJS) $(SCREEN_OBJS) $(UTIL_OBJS)

AS=nasm
AS_FORMAT=elf
CC=gcc
AR=ar
ARFLAGS=-rs
ARCH=i586

KERNEL_CFLAGS=-ffreestanding -nostdlib -fno-builtin -Wall -Winline -Wmissing-declarations -Wredundant-decls -finline-functions -fpic -march=${ARCH} -m32 -Iinclude/ -fno-leading-underscore
CFLAGS = $(KERNEL_CFLAGS)

default : package

package : kernel.ld ${KERNEL_OBJS}
	@echo "(LD) ${KERNEL_FILE}"
	ld -melf_i386 -T kernel.ld -o ${KERNEL_FILE} $(KERNEL_OBJS) 
	@echo "Sanity Check"
	@mbchk ${KERNEL_FILE}

######
# assembly dependencies
######
%.o : %.asm
	@echo "(AS) $<"
	@$(AS) -f $(AS_FORMAT) -o $@ $<

######
# cpp files
######
%.o : %.c
	@echo "(CC) $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

######
# generate dependencies
######
%.dep : %.c
	@echo "(DEP) $<"
	@set -e; rm -f $@; \
		$(CC) -M $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

C_SRCS=$(subst .o,.c,$(KERNEL_OBJS))
MAKEFILES_D=$(subst .c,.dep,$(C_SRCS))

-include $(MAKEFILES_D)

clean :
	rm -f $(KERNEL_OBJS)
	rm -f ${KERNEL_FILE}
	rm -f $(MAKEFILES_D)

image : package
	@cd build-tools; ./create_image --clean -f PoseidonOS.img
	@cd build-tools; ./create_image --create -f PoseidonOS.img
	@mv build-tools/PoseidonOS.img .

