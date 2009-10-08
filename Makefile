default : run

package : image

compile :
	@make -C kernel

clean : clean_image
	@make -C kernel clean

clean_image :
	@rm -f PoseidonOS.img
	@cd build-tools; ./create_image --clean -f PoseidonOS.img

image : compile
	@cd build-tools; ./create_image --clean -f PoseidonOS.img
	@cd build-tools; ./create_image --create -f PoseidonOS.img
	@mv build-tools/PoseidonOS.img .

PoseidonOS.img : image

run : PoseidonOS.img
	bochs -q -f bochs.conf
