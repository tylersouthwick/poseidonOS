
BASE_URL=poseidonos.sourceforge.net
IMG_NAME=poseidonos.img

all: 
	cd kernel; make

bochs : image
	bochs -q

image: poseidonos.img
	mount floppy/
	cp -f kernel/kernel.elf floppy/
	umount floppy/

clean:
	cd kernel; make clean

poseidonos.img:
	wget ${BASE_URL}/${IMG_NAME}

