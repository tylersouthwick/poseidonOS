POSEIDON_ROOT=/home/northfuse/workspace/poseidonos
SRC_ROOT=${POSEIDON_ROOT}
BUILD_ROOT=${POSEIDON_ROOT}/build
DOC_ROOT=${POSEIDON_ROOT}/doc

KERNEL_ROOT=${SRC_ROOT}/kernel
DRIVERS_ROOT=${KERNEL_ROOT}/drivers
UTIL_ROOT=${KERNEL_ROOT}/util

AS_FORMAT=elf

CC = gcc
AS = nasm

AR = ar
ARFLAGS = -rs

KERNEL_INCLUDE=${KERNEL_ROOT}/include
KERNEL_INCLUDE_DIR=-I${KERNEL_INCLUDE}
DRIVER_INCLUDE_DIR=-I${DRIVERS_ROOT}/include

KERNEL_CFLAGS = -ffreestanding -nostdlib -fno-builtins -Wall -Winline -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -finline-functions 

CFLAGS = ${KERNEL_CFLAGS} ${KERNEL_INCLUDE_DIR} ${DRIVER_INCLUDE_DIR}


compile : ${LIB_NAME}.a
${LIB_NAME}.a: $(C_OBJS) ${ASM_OBJS}
	$(AR) $(ARFLAGS) ${LIB_NAME}.a $(C_OBJS) ${ASM_OBJS}

clean:
	rm -f ${C_OBJS} ${ASM_OBJS} ${LIB_NAME}.a

#C dependencies created by 'make dep'
include ${KERNEL_ROOT}/dependencies.mk

#looking for a dependency that wasn't already found?
%.o : %.asm
	${AS} -f ${AS_FORMAT} -o $@ $?

