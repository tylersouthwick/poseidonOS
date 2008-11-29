
AS_FORMAT=aout
AS=nasm
AR=ar
ARFLAGS=-rs
ARCH=i586
STATIC_LIBRARY_CFLAGS=-ffreestanding -nostdlib -fno-builtin -Wall -Winline -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -finline-functions -fpic -march=${ARCH} -m32
STATIC_LIBRARY_INCLUDES=../includes
LD_TARGET=i386linux

CFLAGS=${STATIC_LIBRARY_CFLAGS} -I${STATIC_LIBRARY_INCLUDES}

default : ${APP_NAME}.app

${APP_NAME}.app : ${ASM_OBJS} ${C_OBJS}
	@echo "Building app ${APP_NAME}"
	ld -m${LD_TARGET} -o ${APP_NAME}.app ${C_OBJS} ${ASM_OBJS} ${LIBS}

############################################compile stuff#####################################

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
##############################################################################################

clean:
	rm -f ${ASM_OBJS}
	rm -f ${C_OBJS}
	rm -f ${LIB_NAME}

depclean : clean
	rm -f *.dep
