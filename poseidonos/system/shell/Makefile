SHELL_OBJS=shell.o
AS=nasm
AS_TYPE=-f bin

default: shell.app

shell.o : shell.asm
	@echo "(AS) shell.asm"
	@${AS} ${AS_OPTS} ${AS_TYPE} -o $@ $<

shell.app : ${SHELL_OBJS}
	@echo "(LD) shell.app"
	@cp shell.o shell.app
	@mv shell.app ../shell.app

clean :
	rm -f *.o
	rm -f shell.app
	

