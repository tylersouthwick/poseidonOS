C_OBJS= psh.o \
	tokenizer.o \
	linked_list.o

EXEC_NAME=psh
#####################################
## Variables
####################################

CC=gcc
AR=ar
ARFLAGS=-rs

CFLAGS=-ffreestanding -fno-builtin -Wall -Winline -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -finline-functions -fpic 

#####################################
## DON'T EDIT BELOW THIS LINE
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
# build exec
######
compile : $(EXEC_NAME)
$(EXEC_NAME): $(C_OBJS) 
	@$(CC) $(CFLAGS) $(C_OBJS) -o psh

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
%.dep : %.c
	@echo "(DEP) $<"
	@set -e; rm -f $@; \
		$(CC) -M $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

C_SRCS=$(subst .o,.c,$(C_OBJS))
MAKEFILES_D=$(subst .c,.dep,$(C_SRCS))

######
# clean up temporary files
######
clean:
	@echo "(RM) $(C_OBJS) $(EXEC_NAME)"
	@rm -f $(C_OBJS) $(ASM_OBJS) $(EXEC_NAME)

######
# clean up ALL temporary files
######
depclean : clean
	@echo "(RM) $(MAKEFILES_D)"
	@rm -f $(MAKEFILES_D)
	@rm -f *.dep.*

