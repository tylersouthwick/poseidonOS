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
LD = ld
LDFLAGS = -Tkernel.ld

AR = ar
ARFLAGS = -rs

KERNEL_INCLUDE=${KERNEL_ROOT}/include
KERNEL_INCLUDE_DIR=-I${KERNEL_INCLUDE}
DRIVER_INCLUDE_DIR=-I${DRIVERS_ROOT}/include

KERNEL_CFLAGS = -ffreestanding -nostdlib -fno-builtins -Wall -Winline

CFLAGS = ${KERNEL_CFLAGS} ${KERNEL_INCLUDE_DIR} ${DRIVER_INCLUDE_DIR}

poseidonos : compile

###include dependencies
#${KERNEL_INCLUDE}/kutil.h : ${KERNEL_INCLUDE}/util/map.h
${KERNEL_INCLUDE}/kernel.h : ${KERNEL_INCLUDE}/screen.h ${KERNEL_INCLUDE}/idt.h ${KERNEL_INCLUDE}/mm/mm.h ${KERNEL_INCLUDE}/string.h ${KERNEL_INCLUDE}/gdt.h ${KERNEL_INCLUDE}/multitasking.h ${KERNEL_INCLUDE}/scheduler.h ${KERNEL_INCLUDE}/drivers.h ${KERNEL_INCLUDE}/devicemanager.h ${KERNEL_INCLUDE}/bios.h ${KERNEL_INCLUDE}/irq.h
${KERNEL_INCLUDE}/devices.h : ${KERNEL_INCLUDE}/floppy.h

