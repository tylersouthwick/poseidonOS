#makefile to compile screen.o
include ../rules.mk

SCREEN_OBJS = screen.o

compile: screen.o

###################################compile stuff##################################
screen.o : screen.c kernel.h ktypes.h kdebug.h
##################################################################################

clean:
	rm -f screen.o
