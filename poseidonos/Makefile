
default : binaries

BASE_URL=poseidonos.sourceforge.net
IMAGE_NAME=poseidonos.img
MTOOL_CONFIG=.mtoolconfig

binaries : 
	@make -s -C kernel
	@make -s -C system
	@echo "Now run make install to install the binaries into a floppy image"

bochs : 
	@echo "remember to run make install before make bochs"
	@echo
	@echo "(BOCHS) output can be found in .bochs_out"
	@bochs -q &> .bochs_out &

clean:
	@make -s -C kernel clean
	@make -s -C system clean
	@scripts/install --clean -f ${IMAGE_NAME}

depclean:
	@make -s -C kernel depclean 

${IMAGE_NAME} : 
	@cd scripts;GRUB=/sbin/grub MTOOL_CONFIG=$(MTOOL_CONFIG) ./install --build_floppy -f ../${IMAGE_NAME}

install : ${IMAGE_NAME}
	@echo "(MCOPY) kernel.sys"
	@mcopy -n -o -i ${IMAGE_NAME} kernel/poseidon.sys ::poseidon.sys
