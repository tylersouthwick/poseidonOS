build : libc.h libc.o

HEADER_FILE=../../kernel/include/libc.h

clean :
	rm -f *.o

libc.o : libc.asm
	nasm -felf libc.asm

libc.h : ${HEADER_FILE}
	./generate -p > libc.h

libc.asm : ${HEADER_FILE}
	./generate -a > libc.asm
