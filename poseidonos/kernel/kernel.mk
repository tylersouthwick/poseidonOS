#####################################
## Variables
## change the POSEIDON_ROOT to match your setup
####################################
POSEIDON_ROOT=/home/northfuse/workspace/poseidonos

AS = nasm
AS_FORMAT=elf
CC = gcc
AR = ar
ARFLAGS = -rs

KERNEL_CFLAGS = -ffreestanding -nostdlib -fno-builtins -Wall -Winline -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -finline-functions -fpic 

#####################################
## DON't EDIT BELOW THIS LINE
## unless you know what you're doing
#####################################

################
## build variables
################
SRC_ROOT=$(POSEIDON_ROOT)
KERNEL_ROOT=$(SRC_ROOT)/kernel
KERNEL_INCLUDE=$(KERNEL_ROOT)/include

CFLAGS = $(KERNEL_CFLAGS) -I$(KERNEL_INCLUDE)

###############
## targets
###############

######
# build library
######
compile : $(LIB_NAME).a
$(LIB_NAME).a: $(C_OBJS) $(ASM_OBJS)
	$(AR) $(ARFLAGS) $(LIB_NAME).a $(C_OBJS) $(ASM_OBJS)

######
# assembly dependencies
######
%.o : %.asm
	$(AS) -f $(AS_FORMAT) -o $@ $?

######
# generate dependencies
######
%.d : %.c
	@set -e; rm -f $@; \
		$(CC) -M $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

C_SRCS=$(subst .o,.c,$(C_OBJS))
MAKEFILES_D=$(subst .c,.d,$(C_SRCS))
include $(MAKEFILES_D)

######
# clean up temporary files
######
clean:
	rm -f $(C_OBJS) $(ASM_OBJS) $(LIB_NAME).a 

######
# clean up ALL temporary files
######
depclean : clean
	rm -f $(MAKEFILES_D)
