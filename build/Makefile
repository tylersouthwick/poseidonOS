all: 
	cd src; make

image: poseidonos.img
	mount floppy/
	cp -f build/kernel.elf floppy/
	umount floppy/

clean:
	cd src; make clean
	rm -f build/*.*

poseidonos.img:
	wget students.cs.byu.edu/~tylers2/poseidonos.img

