.PHONY : default package run clean clean_image test

default : run

package : PoseidonOS.img

clean : clean_image
	@make -C kernel clean
	@make -C apps clean

test : 
	@make -C kernel test
	@make -C apps test

clean_image :
	@rm -f PoseidonOS.img
	@cd build-tools; ./create_image --clean -f PoseidonOS.img

PoseidonOS.img : 
	@make -C kernel
	@make -C apps 
	@cd build-tools; ./create_image --clean -f PoseidonOS.img
	@cd build-tools; ./create_image --create -f PoseidonOS.img
	@mv build-tools/PoseidonOS.img .


run : clean_image PoseidonOS.img
	bochs -q -f bochs.conf
