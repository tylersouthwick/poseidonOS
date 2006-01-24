
default : binaries

BASE_URL=poseidonos.sourceforge.net
IMAGE_NAME=poseidonos.img
MTOOL_CONFIG=.mtoolconfig

binaries : 
	@POSEIDON_ROOT=${PWD} make -s -C kernel
	@make -s -C system
	@echo "Now run make install to install the binaries into a floppy image"

bochs : install
	@echo "remember to run make install before make bochs"
	@echo
	@bochs -q 

generic_clean :
	@make -s -C system clean
	@scripts/install --clean -f ${IMAGE_NAME}
	@rm -f .bochs_out
	@echo "removing apidocs"
	@rm -fR apidocs

clean:
	@POSEIDON_ROOT=${PWD} make -s -C kernel clean
	@make -s generic_clean

depclean: 
	@POSEIDON_ROOT=${PWD} make -s -C kernel depclean 
	@make -s generic_clean

${IMAGE_NAME} : 
	@cd scripts;GRUB=/sbin/grub MTOOL_CONFIG=$(MTOOL_CONFIG) ./install --build_floppy -f ../${IMAGE_NAME}

install : binaries ${IMAGE_NAME}
	@echo "(MCOPY) kernel.sys"
	@mcopy -n -o -i ${IMAGE_NAME} kernel/poseidon.sys ::poseidon.sys
	@echo "(MCOPY) shell.app"
	@mcopy -n -o -i ${IMAGE_NAME} system/shell/shell.app ::shell.app

all : 
	@echo "Building binaries...."
	@make -s binaries
	@echo "Making image..."
	@echo "Copying files to image.."
	@make -s install
	@make -s apidocs

force_apidocs : 
	rm -fRv apidocs
	doxygen doxygen.config

apidocs : 
	@make  -s force_apidocs

deploy : apidocs
	tar -jcf poseidonos-apidocs.tar.bz2 apidocs
