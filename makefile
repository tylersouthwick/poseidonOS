default: PoseidonOS.img

kernel :
	@make -C kernel

system :
	@make -C system

image : kernel system
	@make -C kernel
	@cd build-tools; ./create_image --clean -f PoseidonOS.img
	@cd build-tools; ./create_image --create -f PoseidonOS.img
	@mv build-tools/PoseidonOS.img .

run : image
	bochs -q -f bochs.config

clean:
	@make -C kernel clean
	@rm -f PoseidonOS.img
	@cd build-tools; ./create_image --clean -f PoseidonOS.img
