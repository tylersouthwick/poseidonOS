AS=nasm
AS_FORMAT=elf
CC=gcc
AR=ar
ARFLAGS=-rs
ARCH=i586

KERNEL_CFLAGS=-ffreestanding -nostdlib -fno-builtin -Wall -Winline -Wmissing-declarations -Wredundant-decls -finline-functions -fpic -march=${ARCH} -m32 -I${KERNEL_DIR}/kernel/include/ -fno-leading-underscore
CFLAGS = $(KERNEL_CFLAGS)

AR_LIB_NAME=lib.ar

default : ${AR_LIB_NAME}

C_OBJS=$(subst .c,.o,$(C_SOURCE))
ASM_OBJS=$(subst .asm,.o,$(ASM_SOURCE))

${AR_LIB_NAME} : ${C_OBJS} ${ASM_OBJS}
	@echo "(LIB) $@"
	@$(AR) rcs ${AR_LIB_NAME} ${C_OBJS} ${ASM_OBJS}

######
# assembly dependencies
######
%.o : %.asm
	@echo "(ASM) $<"
	@$(AS) -f $(AS_FORMAT) -o $@ $<

######
# cpp files
######
%.o : %.c
	@echo "(GCC) $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

######
# generate dependencies
######
.%.dep : %.c
	@echo "(DEP) $<"
	@set -e; rm -f $@; \
		$(CC) -M $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

MAKEFILES_D=$(addprefix .,$(subst .c,.dep,$(C_SOURCE)))

-include $(MAKEFILES_D)

clean :
	rm -f *.o
	rm -f *.ar
	rm -f .*.dep

