POSEIDON_ROOT=/home/northfuse/workspace/poseidonos
SRC_ROOT=${POSEIDON_ROOT}
BUILD_ROOT=${POSEIDON_ROOT}/build
DOC_ROOT=${POSEIDON_ROOT}/doc

KERNEL_ROOT=${SRC_ROOT}/kernel
DRIVERS_ROOT=${KERNEL_ROOT}/drivers

AS_FORMAT=elf

CC = gcc
AS = nasm
LD = ld
LDFLAGS = -Tkernel.ld

AR = ar
ARFLAGS = -rs

KERNEL_CFLAGS = -ffreestanding -nostdlib -fno-builtins -Wall -Winline
KERNEL_INCLUDE_DIR=-I${KERNEL_ROOT}/include
DRIVER_INCLUDE_DIR=-I${DRIVERS_ROOT}/include

CFLAGS = ${KERNEL_CFLAGS} ${KERNEL_INCLUDE_DIR} ${DRIVER_INCLUDE_DIR}
