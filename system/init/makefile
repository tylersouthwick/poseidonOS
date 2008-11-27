INIT_OBJS=init.o
AS=nasm
AS_TYPE=-f bin

default: init.app

init.o : init.asm
	${AS} ${AS_OPTS} ${AS_TYPE} -o $@ $<

init.app : ${INIT_OBJS}
	cp init.o init.app

clean :
	rm -f *.o
	rm -f init.app
	

