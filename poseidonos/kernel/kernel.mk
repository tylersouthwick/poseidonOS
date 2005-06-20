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

KERNEL_CFLAGS = -ffreestanding -nostdlib -fno-builtins -Wall -Winline -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -finline-functions -fpic 

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
compile : lib$(LIB_NAME).a
lib$(LIB_NAME).a: $(C_OBJS) $(ASM_OBJS)
	@echo "(AR) $<"
	@$(AR) $(ARFLAGS) lib$(LIB_NAME).a $(C_OBJS) $(ASM_OBJS) 2>/dev/null

######
# assembly dependencies
######
%.o : %.asm
	@echo "(AS) $<"
	@$(AS) -f $(AS_FORMAT) -o $@ $<

######
# c files
######
%.o : %.c
	@echo "(CC) $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

######
# generate dependencies
######
%.d : %.c
	@echo "(DEP) $<"
	@set -e; rm -f $@; \
		$(CC) -M $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

C_SRCS=$(subst .o,.c,$(C_OBJS))
MAKEFILES_D=$(subst .c,.d,$(C_SRCS))

ifneq ($(KERNEL_TOP), "y")
-include $(MAKEFILES_D)
endif

ifneq ($(KERNEL_TOP), "y")
tex : $(LIB_NAME).tex
$(LIB_NAME).tex : 
	@echo "(TEX) $(LIB_NAME).tex"
	@java -cp $(POSEIDON_ROOT)/scripts/DocGenerator/DocGenerator.jar  org.northfuse.documentation.DocGenerator $(LIB_NAME).tex $(C_SRCS)
endif

######
# clean up temporary files
######
ifneq ($(KERNEL_TOP), "y")
clean:
	@echo "(RM) $(C_OBJS) $(ASM_OBJS) $(LIB_NAME).a $(LIB_NAME).tex"
	rm -f $(C_OBJS) $(ASM_OBJS) lib$(LIB_NAME).a 
	rm -f $(LIB_NAME).tex
endif

######
# clean up ALL temporary files
######
ifneq ($(KERNEL_TOP), "y")
depclean : clean
	@echo "(RM) $(MAKEFILES_D)"
	rm -f $(MAKEFILES_D)
endif

