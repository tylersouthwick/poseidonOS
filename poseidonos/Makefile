all: 
	cd kernel; make

image: ../poseidonos.img
	mount floppy/
	cp -f kernel/kernel.elf ../floppy/
	umount floppy/

clean:
	cd kernel; make clean

../poseidonos.img:
	wget students.cs.byu.edu/~tylers2/poseidonos.img

