#makefile to compile string.a
include ../rules.mk

STRING_OBJS = string.o string_assembly.o 

default: string.a

string_assembly.o : string.asm ../include/string.h
	$(AS) -f ${AS_FORMAT} -o string_assembly.o string.asm

string.o : string.c ../include/string.h

string.a : ${STRING_OBJS}
	$(AR) $(ARFLAGS) string.a $(STRING_OBJS)
	
clean:
	rm -f string_assembly.o
	rm -f string.o
	rm -f string.a
