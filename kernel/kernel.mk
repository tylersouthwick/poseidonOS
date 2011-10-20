AS=nasm
AS_FORMAT=elf
CC=gcc
AR=ar
ARFLAGS=-rs
ARCH=i586

SHARED_CFLAGS=-I${KERNEL_DIR}/kernel/include/ -std=c99
# -m32 -march=${ARCH}
KERNEL_CFLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -Wall -Winline -Wmissing-declarations -Wredundant-decls -finline-functions -fpic -fno-leading-underscore $(SHARED_CFLAGS)
TEST_CFLAGS=$(CFLAGS) $(SHARED_CFLAGS)

AR_LIB_NAME=lib.a

.PHONY: default clean test

C_OBJS=$(subst .c,.o,$(C_SOURCE))
ASM_OBJS=$(subst .asm,.o,$(ASM_SOURCE))

default : ${AR_LIB_NAME}


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
	@$(CC) -c $(KERNEL_CFLAGS) -o $@ $<

######
# generate dependencies
######
.%.dep : %.c
#	@echo "(DEP) $<"
	@set -e; rm -f $@; \
		$(CC) -M $(KERNEL_CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

MAKEFILES_D=$(addprefix .,$(subst .c,.dep,$(C_SOURCE)))

-include $(MAKEFILES_D)

clean :
	@rm -f *.o
	@rm -f *.a
	@rm -f .*.dep
	@rm -f test.out

test : test.out
ifdef TEST_SOURCE
	./test.out
else
	@echo "no tests" &> /dev/null
endif

test.out : $(TEST_SOURCE)
ifdef TEST_SOURCE
	gcc -DTEST $(TEST_CFLAGS) $(TEST_SOURCE) -o test.out
else
	@echo "no test sources" &> /dev/null
endif
