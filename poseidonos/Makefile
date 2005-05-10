
default : all

BASE_URL=poseidonos.sourceforge.net
IMG_NAME=poseidonos.img

all: 
	cd kernel; make
	cd system; make

bochs : image
	bochs -q

image: poseidonos.img
	mount floppy/
	cp -f kernel/kernel.elf floppy/
	cp -f system/shell/shell.app floppy
	umount floppy/

clean:
	cd kernel; make clean
	cd system; make clean

depclean:
	cd kernel; make depclean

poseidonos.img:
	wget ${BASE_URL}/${IMG_NAME}

